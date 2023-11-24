# Projet-hardware

## Fichiers disponibles :

- sketch_nov23a.ino -> code C++ pour esp32c3
- esp32-action.php -> code php pour rendre disponible les UIDS authorisés
- esp-db.php -> code php pour intéragir avec la base de donnée
- esp32c3_rfid.sql -> copie de la base de donnée SQL

## Modifications à apporter:

### sketch_nov23a.ino
- L27 Remplacer "YOUR_SSID" par le SSID du réseau WIFI utilisé.
- L28 Remplacer "YOUR_PASSWORD" par le mod de passe du réseau WIFI utilisé.
- L31 Remplacer YOUR_IPADRESS par le nom de domaine ou Adresse IP de votre serveur Raspberry.
### esp-db.php
- L6 Remplacer "YOUR_USERNAME" par le nom d'utilisateur de la base de donnée.
- L7 Remplacer "YOUR_PASSWORD" par le mot de passe de l'utilisateur de la base de donnée.

## Composants utilisés : 
- 1 ESP32C3
- 1 RFID-RC522
- 1 LED Verte
- 1 LED Rouge
- 2 résistances de 220 ohm
- 1 Antenne esp32C3
- 1 Breadboard
- 12 cables male-male pour breadboard
 
## Bibliothèques utilisés : 

- WiFi.h : Permet la connexion réseau (locale et Internet) à l'aide du bouclier WiFi Arduino.

- HTTPClient.h : Bibliothèque pour effectuer facilement des requêtes HTTP GET, POST et PUT vers un serveur Web.

- WiFiClientSecure.h : La librairie Arduino <WiFiClientSecure.h> permet d'établir des connexions sécurisées via le protocole HTTPS sur des réseaux Wi-Fi.

- Arduino_JSON.h : La librairie Arduino <Arduino_JSON.h> facilite la manipulation et le traitement des données au format JSON dans les projets Arduino.

- SPI.h : La librairie Arduino <SPI.h> permet la communication série synchrone (SPI - Serial Peripheral Interface) entre périphériques, utilisée notamment pour interagir avec des capteurs, des écrans et d'autres composants.

- MFRC522.h : La librairie Arduino <MFRC522.h> est utilisée pour interagir avec les modules de lecteur RFID (Radio-Frequency Identification) tels que le MFRC522, permettant la lecture et l'écriture de cartes RFID.

## Câblage :

1. **MOSI  D10** (Master Out Slave In) la ligne de données sortantes du maître vers l'esclave.
2. **MISO  D9** (Master In Slave Out) la ligne de données entrantes de l'esclave vers le maître.
3. **SCK  D8** ligne d'horloge générée par le maître qui synchronise la transmission de données entre le maître et l'esclave.
4. **SS  D4** (écrit SDA sur le lecteur) permet de sélectionner un esclave spécifique sur le bus SPI.
5. **RST  D3** sert à réinitialiser le lecteur RFID.
6. **LED rouge  D2** pour alimenter et contrôler la LED rouge.
7. **LED verte  D1** pour alimenter et contrôler la LED verte.
8. **3.3V 3V3** pour alimenter le lecteur RFID.

## Schéma du montage :

   ![image](https://github.com/TheShadowFR/Projet-hardware/assets/117437326/7f908021-9fd4-499e-bce2-0d41651717a7)

