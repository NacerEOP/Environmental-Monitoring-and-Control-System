/*
  CropCare ESP32 — Serveur sur l’ESP32 (pas de PHP / XAMPP)

  API:
  - GET     /api/latest
  - GET     /api/history
  - GET     /api/sensors
  - OPTIONS /api/*  (CORS)

  Capteurs:
  - DHT11 (GPIO4)
  - Humidité sol analog (GPIO34)
  - BH1750 (I2C SDA=21, SCL=20)

  Libraries: DHT (Adafruit), BH1750, ESPAsyncWebServer, AsyncTCP, Preferences, LittleFS.
*/

#include <WiFi.h>
#include <Wire.h>
#include <BH1750.h>
#include <DHT.h>
#include <time.h>
#include <Preferences.h>
#include <LittleFS.h>
#include <ESPAsyncWebServer.h>

// ------------------- Serveur -------------------
AsyncWebServer server(80);

// ------------------- Dernières valeurs -------------------
float g_temp = 0, g_hum = 0, g_soil = 0, g_lux = 0;
bool BH_OK = false;

// ------------------- Historique en RAM -------------------
#define HISTORY_MAX 50
struct Reading
{
  float temperature;
  float humidity;
  float soil;
  float light;
  char at[28]; // ISO date
};
Reading historyBuf[HISTORY_MAX];
int historyCount = 0;
int historyIndex = 0; // prochaine écriture (circular)

// ------------------- Pins -------------------
#define I2C_SDA_PIN 21
#define I2C_SCL_PIN 20
#define DHTPIN 4
#define DHTTYPE DHT11
#define SOIL_PIN 1 // <-- IMPORTANT: analog sur ESP32 (ex: 34). Pas 1.

// ------------------- Wi-Fi (flash) -------------------
#define MAX_SSID_LEN 33
#define MAX_PASS_LEN 65
Preferences prefs;
char WIFI_SSID[MAX_SSID_LEN];
char WIFI_PASS[MAX_PASS_LEN];

// ------------------- Capteurs -------------------
DHT dht(DHTPIN, DHTTYPE);
BH1750 lightMeter;
int SOIL_DRY = 3200;
int SOIL_WET = 1400;

// ------------------- Timing -------------------
unsigned long lastSendMs = 0;
const unsigned long SEND_EVERY_MS = 5000;

// ------------------- CORS helper (FIX) -------------------
static inline void addCors(AsyncWebServerResponse *res)
{
  res->addHeader("Access-Control-Allow-Origin", "*");
  res->addHeader("Access-Control-Allow-Methods", "GET, OPTIONS");
  res->addHeader("Access-Control-Allow-Headers", "Content-Type");
  res->addHeader("Access-Control-Max-Age", "86400");
}

// ------------------- NTP -------------------
void setupTime()
{
  configTime(0, 0, "pool.ntp.org", "time.google.com");
}

String isoNowUTC()
{
  time_t now;
  time(&now);
  if (now < 100000)
    return ""; // pas encore sync
  struct tm t;
  gmtime_r(&now, &t);
  char buf[30];
  strftime(buf, sizeof(buf), "%Y-%m-%dT%H:%M:%SZ", &t);
  return String(buf);
}

// ------------------- Helpers -------------------
float clampf(float v, float mn, float mx)
{
  if (v < mn)
    return mn;
  if (v > mx)
    return mx;
  return v;
}

float soilPercentFromRaw(int raw)
{
  if (SOIL_DRY == SOIL_WET)
    return 0.0f;
  float pct = 100.0f * (float)(SOIL_DRY - raw) / (float)(SOIL_DRY - SOIL_WET);
  return clampf(pct, 0.0f, 100.0f);
}

// ------------------- Lecture ligne Série -------------------
void readLineOrEmpty(char *buffer, size_t maxLen, uint32_t timeoutMs = 60000)
{
  size_t i = 0;
  uint32_t start = millis();
  while (true)
  {
    while (!Serial.available())
    {
      delay(10);
      if (timeoutMs > 0 && (millis() - start) > timeoutMs)
      {
        buffer[0] = '\0';
        return;
      }
    }
    char c = Serial.read();
    if (c == '\n' || c == '\r')
    {
      if (c == '\r' && Serial.available() && Serial.peek() == '\n')
        Serial.read();
      break;
    }
    if (i < maxLen - 1)
      buffer[i++] = c;
  }
  buffer[i] = '\0';
}

void trimRight(char *s)
{
  int len = (int)strlen(s);
  while (len > 0)
  {
    char c = s[len - 1];
    if (c == ' ' || c == '\t' || c == '\r' || c == '\n')
      s[--len] = '\0';
    else
      break;
  }
}

// ------------------- Flash (NVS) -------------------
void loadCredsFromFlash()
{
  prefs.begin("wifi", true);
  String s = prefs.getString("ssid", "");
  String p = prefs.getString("pass", "");
  prefs.end();

  strncpy(WIFI_SSID, s.c_str(), MAX_SSID_LEN);
  WIFI_SSID[MAX_SSID_LEN - 1] = '\0';
  strncpy(WIFI_PASS, p.c_str(), MAX_PASS_LEN);
  WIFI_PASS[MAX_PASS_LEN - 1] = '\0';
}

void saveCredsToFlash()
{
  prefs.begin("wifi", false);
  prefs.putString("ssid", WIFI_SSID);
  prefs.putString("pass", WIFI_PASS);
  prefs.end();
}

void promptAndMaybeUpdateCreds()
{
  char inputSSID[MAX_SSID_LEN];
  char inputPASS[MAX_PASS_LEN];

  Serial.println();
  Serial.println("----- WiFi credentials -----");
  Serial.print("Saved SSID: ");
  Serial.println(strlen(WIFI_SSID) ? WIFI_SSID : "(none)");

  Serial.println("Enter WIFI SSID (press Enter to keep saved):");
  readLineOrEmpty(inputSSID, MAX_SSID_LEN, 0);
  trimRight(inputSSID);

  Serial.println("Enter WIFI PASSWORD (press Enter to keep saved):");
  readLineOrEmpty(inputPASS, MAX_PASS_LEN, 0);
  trimRight(inputPASS);

  bool changed = false;

  if (strlen(inputSSID) > 0)
  {
    strncpy(WIFI_SSID, inputSSID, MAX_SSID_LEN);
    WIFI_SSID[MAX_SSID_LEN - 1] = '\0';
    changed = true;
  }
  if (strlen(inputPASS) > 0)
  {
    strncpy(WIFI_PASS, inputPASS, MAX_PASS_LEN);
    WIFI_PASS[MAX_PASS_LEN - 1] = '\0';
    changed = true;
  }

  if (changed)
  {
    saveCredsToFlash();
    Serial.println("Saved to flash.");
  }
  else
  {
    Serial.println("Keeping saved credentials.");
  }
}

// ------------------- Historique -------------------
void pushReading(float temperature, float humidity, float soilPct, float lux)
{
  Reading *r = &historyBuf[historyIndex];
  r->temperature = temperature;
  r->humidity = humidity;
  r->soil = soilPct;
  r->light = lux;

  String at = isoNowUTC();
  if (at.length() > 0)
    strncpy(r->at, at.c_str(), sizeof(r->at) - 1);
  else
    strncpy(r->at, "", sizeof(r->at) - 1);
  r->at[sizeof(r->at) - 1] = '\0';

  historyIndex = (historyIndex + 1) % HISTORY_MAX;
  if (historyCount < HISTORY_MAX)
    historyCount++;
}

// ------------------- Routes API -------------------
void setupRoutes()
{
  // LittleFS static (optionnel)
  if (LittleFS.begin(true))
  {
    // Sert la page
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(LittleFS, "/index.html", "text/html; charset=utf-8"); });

    // Force MIME corrects pour ES modules
    server.on("/src/app.js", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(LittleFS, "/src/app.js", "text/javascript"); });
    server.on("/src/config.js", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(LittleFS, "/src/config.js", "text/javascript"); });
    server.on("/src/weather-icons.js", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(LittleFS, "/src/weather-icons.js", "text/javascript"); });
    server.on("/src/styles.css", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(LittleFS, "/src/styles.css", "text/css"); });

    // Optionnel: servir le reste (images, etc.)
    server.serveStatic("/", LittleFS, "/");
  }
  else
  {
    Serial.println("LittleFS mount failed");
  }

  // OPTIONS générique sur /api/*
  server.on("^\\/api\\/.*$", HTTP_OPTIONS, [](AsyncWebServerRequest *request)
            {
    AsyncWebServerResponse *res = request->beginResponse(204);
    addCors(res);
    request->send(res); });

  // GET /api/latest
  auto handleLatest = [](AsyncWebServerRequest *request)
  {
    String at = isoNowUTC();
    String json = "{\"temperature\":" + String(g_temp, 1) +
                  ",\"humidity\":" + String(g_hum, 0) +
                  ",\"soil\":" + String(g_soil, 0) +
                  ",\"light\":" + String(g_lux, 0) +
                  ",\"at\":\"" + at + "\"}";

    AsyncWebServerResponse *res = request->beginResponse(200, "application/json", json);
    addCors(res);
    request->send(res);
  };
  server.on("/api/latest", HTTP_GET, handleLatest);
  server.on("/api/latest/", HTTP_GET, handleLatest);

  // GET /api/history (max 36 points, plus récent en premier)
  server.on("/api/history", HTTP_GET, [](AsyncWebServerRequest *request)
            {
    int n = (historyCount < 36) ? historyCount : 36;
    String out = "[";
    for (int i = 0; i < n; i++)
    {
      int j = (historyIndex - 1 - i + HISTORY_MAX * 2) % HISTORY_MAX;
      Reading *r = &historyBuf[j];
      if (i > 0) out += ",";
      out += "{\"temperature\":" + String(r->temperature, 1) +
             ",\"humidity\":" + String(r->humidity, 0) +
             ",\"soil\":" + String(r->soil, 0) +
             ",\"light\":" + String(r->light, 0) +
             ",\"at\":\"" + String(r->at) + "\"}";
    }
    out += "]";

    AsyncWebServerResponse *res = request->beginResponse(200, "application/json", out);
    addCors(res);
    request->send(res); });
  server.on("/api/history/", HTTP_GET, [](AsyncWebServerRequest *request)
            {
    // même code que /api/history
    int n = (historyCount < 36) ? historyCount : 36;
    String out = "[";
    for (int i = 0; i < n; i++)
    {
      int j = (historyIndex - 1 - i + HISTORY_MAX * 2) % HISTORY_MAX;
      Reading *r = &historyBuf[j];
      if (i > 0) out += ",";
      out += "{\"temperature\":" + String(r->temperature, 1) +
             ",\"humidity\":" + String(r->humidity, 0) +
             ",\"soil\":" + String(r->soil, 0) +
             ",\"light\":" + String(r->light, 0) +
             ",\"at\":\"" + String(r->at) + "\"}";
    }
    out += "]";

    AsyncWebServerResponse *res = request->beginResponse(200, "application/json", out);
    addCors(res);
    request->send(res); });

  // GET /api/sensors (sans "at")
  server.on("/api/sensors", HTTP_GET, [](AsyncWebServerRequest *request)
            {
    String json = "{\"temperature\":" + String(g_temp, 1) +
                  ",\"humidity\":" + String(g_hum, 0) +
                  ",\"soil\":" + String(g_soil, 0) +
                  ",\"light\":" + String(g_lux, 0) + "}";

    AsyncWebServerResponse *res = request->beginResponse(200, "application/json", json);
    addCors(res);
    request->send(res); });
}

// ------------------- Connexion Wi-Fi (bloquante) -------------------
bool connectWifiBlocking(uint32_t timeoutMs = 30000)
{
  if (strlen(WIFI_SSID) == 0)
  {
    Serial.println("No SSID stored. Not connecting.");
    return false;
  }

  WiFi.mode(WIFI_STA);
  WiFi.disconnect(true, true);
  delay(300);

  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.print("Connecting to WiFi");

  uint32_t start = millis();
  while (WiFi.status() != WL_CONNECTED && (millis() - start) < timeoutMs)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("WiFi connection failed (timeout).");
    return false;
  }

  Serial.println("Connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // setup routes + start server (une seule fois)
  static bool started = false;
  if (!started)
  {
    setupRoutes();
    server.begin();
    started = true;
  }

  return true;
}

// ------------------- Setup / Loop -------------------
void setup()
{
  Serial.begin(115200);
  delay(200);
  Serial.println();
  Serial.println("CropCare ESP32 - Booting...");

  loadCredsFromFlash();
  promptAndMaybeUpdateCreds();

  bool ok = connectWifiBlocking(30000);

  // I2C + BH1750
  BH_OK = false;
  Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN);
  BH_OK = lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE);
  if (!BH_OK)
    Serial.println("BH1750 init failed.");

  // DHT
  dht.begin();

  // ADC
  analogReadResolution(12);

  if (ok)
    setupTime();
}

void loop()
{
  if (millis() - lastSendMs < SEND_EVERY_MS)
    return;
  lastSendMs = millis();

  static unsigned long lastRetry = 0;
  if (WiFi.status() != WL_CONNECTED)
  {
    if (millis() - lastRetry > 10000)
    {
      lastRetry = millis();
      if (connectWifiBlocking(30000))
        setupTime();
    }
    return;
  }

  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  if (isnan(humidity) || isnan(temperature))
  {
    Serial.println("DHT11 read failed");
    return;
  }

  int soilRaw = analogRead(SOIL_PIN);
  float soilPct = soilPercentFromRaw(soilRaw);

  float lux = 0;
  if (BH_OK)
    lux = lightMeter.readLightLevel();
  if (lux < 0)
    lux = 0;

  g_temp = temperature;
  g_hum = humidity;
  g_soil = soilPct;
  g_lux = lux;

  Serial.printf("T=%.1fC H=%.0f%% SoilRaw=%d Soil=%.0f%% Lux=%.0f\n",
                temperature, humidity, soilRaw, soilPct, lux);

  pushReading(temperature, humidity, soilPct, lux);
}
