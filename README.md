<img width="1111" height="807" alt="image" src="https://github.com/user-attachments/assets/ec63890f-814c-4f56-af90-0cbaad861153" />
<img width="1776" height="322" alt="image" src="https://github.com/user-attachments/assets/971c25fe-5097-406f-9e56-53a8800bb5e3" />

```
Shape the future with cutting-edge technology. Network with industry leaders. Win
amazing prizes.
28-29 January 2026 | CESI Algiers Campus
TEAM-6
```
### IDÉE DU PROJET..............................................................................................................

L’automatisation de la culture des plantes et de l’agriculture en général, en s’appuyant sur
l’analyse des données environnementales agricoles.

### PROBLÉMATIQUE.............................................................................................................

#### Le défi actuel................................................................................................................

Aujourd'hui, les agriculteurs prennent encore beaucoup de décisions à l'aveugle : irrigation,
aération, exposition au soleil... sans données précises et en temps réel. Avec le changement
climatique, ces décisions deviennent de plus en plus risquées et coûteuses.

#### Les conséquences.......................................................................................................

Une mauvaise décision peut entraîner :
● Des pertes de rendement importantes
● Un gaspillage significatif d'eau
● Le développement de maladies des plantes, souvent causés par une irrigation
mal maîtrisée ou des conditions environnementales non surveillées


#### L'urgence d'agir............................................................................................................

Le climat change plus vite que les pratiques agricoles. Les capteurs IoT et l'analyse de
données sont aujourd'hui accessibles, peu coûteux et fiables. C'est le moment idéal pour
passer d'une agriculture basée sur l'intuition à une agriculture basée sur les données.

### SOLUTION PROPOSÉE....................................................................................................

Un dispositif IoT (Internet of Things) qui, grâce à plusieurs capteurs, permet de collecter des
données sur l’environnement (température, humidité, luminosité) et, à partir de celles-ci, de
contrôler automatiquement (activation/désactivation) des équipements agricoles aux
moments appropriés.

### EXPLICATION BREF.........................................................................................................

Le dispositif IoT aura pour cerveau un microcontrôleur de type ESP32-S3 WROOM-1,
équipé d’une antenne Wi-Fi/Bluetooth.
L’utilisateur pourra, via une interface web (site HTML / dashboard), configurer le système,
par exemple : activer ou désactiver des équipements, définir des seuils d’activation pour les
équipements, etc.


## SOMMAIRE

- TEAM-6....................................................................................................................................
   - IDÉE DU PROJET..............................................................................................................
   - PROBLÉMATIQUE.............................................................................................................
      - Le défi actuel................................................................................................................
      - Les conséquences.......................................................................................................
      - L'urgence d'agir............................................................................................................
   - SOLUTION PROPOSÉE....................................................................................................
   - EXPLICATION BREF.........................................................................................................
   - 1/ Etude du problème /marché...........................................................................................
   - 2/Notre positionnement......................................................................................................
      - Boîtier IoT :...................................................................................................................
      - Service.........................................................................................................................
   - 3/Concurrence potentielle :................................................................................................
   - 4/PLAN D’ACTION - ROADMAP........................................................................................
   - 5/ Prise en charge et financement....................................................................................
   - 6/ choix des locaux / région..............................................................................................
      - Public visé...................................................................................................................
      - Segments prioritaires..................................................................................................
      - Défis spécifiques de ces exploitations........................................................................
   - 7/ Couverture Théorique et estimation de prix.................................................................
   - 8/ Étude de Risque Économique......................................................................................
      - 1.2 Risque Concurrentiel............................................................................................
      - 1.3 Risque de Concentration Géographique..............................................................
   - 9/ Specification Techniques..............................................................................................
      - Capteurs et composants du prototype.......................................................................
      - Services externes.......................................................................................................
      - Évolution vers un produit final....................................................................................
      - Contrôle d’équipements agricoles..............................................................................
      - Fonctionnement sans accès Internet.........................................................................


### 1/ Etude du problème /marché...........................................................................................

L’Algérie est un pays en stress hydrique c'est-à-dire une nation où la demande en eau (pour
la consommation, l'agriculture, l'industrie) dépasse les ressources en eau douce disponibles.
On parle de stress hydrique quand on est en dessous du seuil de 1700 M3 d’eau par
habitant par an, on est à moins de 500 m³/an/habitant).
L’agriculture consomme ≈ 60–65 % de l’eau disponible.
Pourquoi avons- nous décidé de viser les serres maraîchères?
Les serres maraîchères (tomate, poivron, concombre, fraise...) sont :
-À fort rendement
-À fort potentiel d’optimisation de l’eau
Prêtes technologiquement (plus que l’agriculture extensive) système de production agricole
caractérisé par une faible utilisation d'intrants (engrais, pesticides, énergie) et de
main-d'œuvre par rapport à l'étendue des terres cultivées.
Économiquement et stratégiquement, les serres maraîchères sont la MEILLEURE cible
initiale.
Voici Un article qui d’avril 2025 posté par ECOTIMES à propos de l’évolution des cultures
maraîchères :
https://ecotimesdz.com/le-maraichage-en-algerie-un-secteur-en-pleine-expansion/


« L’agriculture algérienne, en particulier le secteur du maraîchage, connaît depuis deux
décennies une transformation remarquable. »
« Les cultures sous serre ont connu une croissance de 168 % entre 2010 et 2021. »
« La superficie des cultures maraîchères [...] a connu une légère tendance à la hausse au
cours de la période 2010-2021. »
« Celle-ci est passée de 429 417 ha à 517 425 ha, soit une évolution de 20 %. »
Pour référence un stade de foot professionnel à une taille de 0.7 ha, cela fait plus d’une
centaine de milliers de terrains de foot.
< Elles [les cultures maraîchères] génèrent près de 40 % de la production agricole totale. »
https://www.algerianagripreneurs.dz/

### 2/Notre positionnement......................................................................................................

Réduire la consommation d’eau de 20 à 40 % tout en améliorant le rendement
Produit

#### Boîtier IoT :...................................................................................................................

##### - ESP

- DHT11 (température / humidité)
- BH1750 (luminosité)
- Capteur humidité sol
- Multiplexeur
- Options multi sensor

#### Service.........................................................................................................................

- Dashboard web / mobile
- Alertes (sécheresse, sur-arrosage)
- Aide à la décision (quand arroser)


### 3/Concurrence potentielle :................................................................................................

**Concurrence Approche Niveau Liens avec projet**
AgriLink Plateforme smart
farming
Algérien Oui surveillance &
alertes
Farmonaut Monitoring global +
données
International /
Algérie
Oui agritech /
irrigation
Qfarming / AirCrop /
TerraLINK
Agriculture numérique Algérien Oui/potentiel client ou
compétiteur
AITECH Plateforme gestion
d’exploitation
Algérien Oui/proche mais plus
logiciel cloud
FILAHATI Serres automatisées Algérien
Seul filahati vise les serres, donc réel potentiel concurrence ou/ client, mais leur objectif c’est
plus d’avoir une serre automatisée pas un système de monitoring.


AITECH est une **plateforme de gestion agricole** qui :
-Utilise IoT et technologies cloud
-Permet de gérer l’exploitation agricole
-Optimise les rendements via des recommandations, collecte de données, alertes, etc.
-Winner de startup concours en 2021


### 4/PLAN D’ACTION - ROADMAP........................................................................................

Pour le build up de traction initialement on mise sur les conférences :
Salon International de l’Investissement dans le secteur de l’Agriculture Saharienne (5-
janvier, Ouargla) : Focus sur les opportunités de développement agricole dans le Sud.
AGRI PRO EXPO 2026 (21-24 janvier, Oran) : 8ème édition axée sur l'agriculture, l'élevage
et l'investissement.
DJAZAGRO (12-15 avril, Alger - SAFEX) : Salon de référence pour la production
agroalimentaire, emballage et transformation.
SIPSA-FILAHA (18-21 mai, Alger) : Salon international de l'agriculture, de l'élevage et de
l'agro-industrie.
AGREST-EXPO (28-31 octobre, Constantine) : 5ème édition axée sur l'élevage, la
céréaliculture et l'arboriculture dans l'Est.
Foire de la Production algérienne (FPA) (17-26 décembre, Alger) : Vitrine de l'industrie
agroalimentaire nationale.


### 5/ Prise en charge et financement....................................................................................

Pour prise en charge / financement :
asf.dz
l’asf propose jusqu à
150 millions DA par projet, ciblant des secteurs stratégiques comme l'agritech.


**Incubateurs :**
Algeria Venture
ANSEJ (ex-)
Incubateurs universitaires

### 6/ choix des locaux / région..............................................................................................

#### Public visé...................................................................................................................

Notre solution s'adresse aux serres maraîchères de production intensive, particulièrement
dans le sud algérien où le climat aride rend le pilotage environnemental critique.

#### Segments prioritaires..................................................................................................

**Les grandes exploitations sous serre**
● Groupe Souakri : projet de 1000 ha à Adrar
● Groupe Tahraoui : 400 ha à M'ziraa
● Production orientée export avec besoin d'optimisation du rendement et de la
qualité
**La région de Biskra**
● Concentration de 54% de la production nationale sous serre
● Centaines d'exploitations moyennes
● Besoin d'un système accessible et adapté au climat saharien

#### Défis spécifiques de ces exploitations........................................................................

```
● Chaleur extrême
● Gestion précise et critique de l'eau
● Risques sanitaires amplifiés par les conditions climatiques
```

### 7/ Couverture Théorique et estimation de prix.................................................................

Une serre maraîchère a une surface typiquement comprise entre 500 et 1000 m2.
La couverture de nos capteurs de sols surtout est comprise entre 50 et 100 m^
**Sensibilité accrue Prix DA**
DHT22 plus précis ~ 1 700 DA
Capteur sol capacitif haut
gamme

##### ~ ~1 500–2 000 DA

##### BH1750 ~ 1 000–1 500 DA

```
Boîtier/PCB+ ~ 2 000–3 000 DA
```

binarytech-dz.com
Dans le cas d’une précision minimale : serre de 500 m
**_Élément Coût unitaire
(DA)
Quantité Coût total (DA)_**
_ESP32_^3 500 1 3 
_DHT11_^750 1 
_BH1750_^1 000 1 1 
_Capteur sol capacitif_^800 5 4 
_Multiplexeur_^1 500 1 1 
_PCB + boîtier +
câbles_

##### — — 2 000

```
Alimentation —^ —^1 
COÛT TOTAL (MIN)
```
##### 15 250 DA

**_MARGE DE 40%_**

##### 25 000 – 26 000 DA /

**serre**
^^
Serre de 1000 m
**_Élément Coût unitaire
(DA)
Quantité Coût total (DA)_**


```
ESP32^3 500 1 3 
DHT11^750 1 
BH1750^1 000 1 1 
Capteur sol capacitif^800 20 16 
Multiplexeur^2 000 1 2 
PCB + boîtier + câbles —^ —^2 
Alimentation —^ —^1 
COÛT TOTAL (MAX
Marge de 40
pourcents
```
##### 28 250 DA

##### 46 000 – 48 000 DA /

```
serre
```
### 8/ Étude de Risque Économique......................................................................................

Risques Stratégiques et de Marché
Risque de Timing et d'Adoption
Risque élevé : Bien que le marché soit en expansion (+168% pour les serres entre
2010-2021), l'adoption de technologies IoT par des agriculteurs traditionnels reste incertaine.
Impact financier : Retard de 12-18 mois dans l'atteinte du seuil de rentabilité
Solution/alternative : Cibler d'abord les grandes exploitations (Groupe Souakri, Groupe
Tahraoui) qui ont les moyens et la culture d'innovation

#### 1.2 Risque Concurrentiel............................................................................................

Risque modéré : Présence de concurrents établis (AITECH - winner 2021, AgriLink,
Farmonaut)


Impact : Pression sur les prix difficulté à gagner des parts de marché
Solution/alternative :
Différenciation par spécialisation serre maraîchère + climat saharien
Partenariats plutôt que confrontation (FILAHATI pourrait être client)
Prix agressif initial pour pénétration rapide

#### 1.3 Risque de Concentration Géographique..............................................................

Risque modéré : Dépendance à 2 régions (Biskra 54%, El Oued ~40% de la production)
Impact : Vulnérabilité aux chocs régionaux (climat, politique locale)
Solution/alternative : Expansion progressive vers Adrar et autres régions du sud

### 9/ Specification Techniques..............................................................................................

Le dispositif développé repose sur un **microcontrôleur ESP32 S3 WROOM-1** , équipé d’une
connectivité **Wi-Fi et Bluetooth** , ce qui en fait un système **IoT (Internet of Things)**.
L’ESP32 se connecte à un réseau Wi-Fi afin d’ **héberger localement une interface web**
accessible depuis un navigateur. Cette interface permet aux utilisateurs de consulter en
temps réel les données collectées par les capteurs grâce à une **API embarquée**
directement sur le microcontrôleur.
Le site web est développé à l’aide des technologies **HTML, CSS et JavaScript**.


#### Capteurs et composants du prototype.......................................................................

Le prototype intègre les composants suivants :
● **ESP32 S3 WROOM-**
● **Capteur de température et d’humidité DHT**
● **Capteur de luminosité BH**


● **Capteur(s) d’humidité du sol**
Les données mesurées par ces capteurs sont traitées par l’ESP32 puis rendues accessibles
aux utilisateurs via l’interface web.

#### Services externes.......................................................................................................

Lorsque l’accès à Internet est disponible, le site hébergé par l’ESP32 peut également
exploiter une **API météo open source** , permettant d’afficher des informations
météorologiques externes en complément des données locales.


#### Évolution vers un produit final....................................................................................

Dans une version future et plus aboutie, le projet pourrait évoluer vers un **produit fini**
intégrant :
● Un **boîtier étanche** adapté à un environnement agricole.
● Un **PCB personnalisé** regroupant l’ESP32 et les différents composants
électroniques.
● Une **extension du nombre d’entrées/sorties** , rendue possible grâce à l’utilisation
de composants abordables tels que des **multiplexeurs** et des **shift registers** ,
supprimant ainsi les limitations liées au nombre de broches du microcontrôleur.
● Une **batterie adaptée** assurant la mobilité du dispositif.
Afin d’optimiser l’autonomie, l’ESP32 devra mettre en œuvre des mécanismes d’ **économie
d’énergie** , notamment en désactivant les services et sous-systèmes non utilisés à un instant
donné.

#### Contrôle d’équipements agricoles..............................................................................

Une version avancée du dispositif pourrait également permettre le **contrôle à distance
d’équipements agricoles** , tels que :
● Pompes
● Vannes
● Lampes UV
● Autres équipements électriques
L’ESP32 serait alors capable d’activer ou de désactiver ces équipements à l’aide de **relais**
ou **d’interrupteurs électroniques** , avec ou sans connexion filaire selon l’architecture
choisie.

#### Fonctionnement sans accès Internet.........................................................................

En cas d’indisponibilité d’Internet dans la zone géographique, l’ESP32 peut fonctionner en
**mode point d’accès Wi-Fi (Access Point)**.
Les utilisateurs pourront alors se connecter directement au réseau Wi-Fi de l’ESP32 et
accéder à l’interface web locale sans dépendre d’une infrastructure réseau externe.
**FIN DU DOCUMENT**

