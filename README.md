# Projet-hardware

## Composants utilisés : 
1 ESP32C3
1 RFID-RC522
1 LED Verte
1 LED Rouge
2 résistances de 220 ohm
1 Antenne esp32C3
1 Breadboard
12 cables male-male pour breadboard
 
## Bibliothèques utilisés : 

WiFi.h : Permet la connexion réseau (locale et Internet) à l'aide du bouclier WiFi Arduino.

HTTPClient.h : Bibliothèque pour effectuer facilement des requêtes HTTP GET, POST et PUT vers un serveur Web.

WiFiClientSecure.h : La librairie Arduino <WiFiClientSecure.h> permet d'établir des connexions sécurisées via le protocole HTTPS sur des réseaux Wi-Fi.

Arduino_JSON.h : La librairie Arduino <Arduino_JSON.h> facilite la manipulation et le traitement des données au format JSON dans les projets Arduino.

SPI.h : La librairie Arduino <SPI.h> permet la communication série synchrone (SPI - Serial Peripheral Interface) entre périphériques, utilisée notamment pour interagir avec des capteurs, des écrans et d'autres composants.

MFRC522.h : La librairie Arduino <MFRC522.h> est utilisée pour interagir avec les modules de lecteur RFID (Radio-Frequency Identification) tels que le MFRC522, permettant la lecture et l'écriture de cartes RFID.

## Câblage 

MOSI - D10
MISO - D9
SCK - D8
SDA - D4
RST - D3
LED rouge - D2
LED verte -  D1 
