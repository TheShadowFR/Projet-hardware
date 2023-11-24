/*
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/control-esp32-esp8266-gpios-from-anywhere/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/

#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include <Arduino_JSON.h>
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         D3          // Configurable, see typical pin layout above
#define SS_PIN          D5         // Configurable, see typical pin layout above
#define redPin       D2
#define greenPin     D1

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance
JSONVar keys = "";

const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

//Your IP address or domain name with URL path
const char* serverName = "https://YOUR_IPADRESS/esp32-action.php?action=authorized_uid";

// Update interval time set to 5 seconds
const long interval = 5000;
unsigned long previousMillis = 0;

String auid;
int badgegood = 0;

void setup() {
  Serial.begin(115200);

  pinMode(D2,OUTPUT);
  // digitalWrite(D2,HIGH);
  pinMode(D1,OUTPUT);
  // digitalWrite(D1,LOW);

  while (!Serial);        // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
    SPI.begin();            // Init SPI bus
    mfrc522.PCD_Init();        // Init MFRC522
    delay(4);                // Optional delay. Some board do need more time after init to be ready, see Readme
    mfrc522.PCD_DumpVersionToSerial();    // Show details of PCD - MFRC522 Card Reader details
    Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
  
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) { 
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  unsigned long currentMillis = millis();
  
  if(currentMillis - previousMillis >= interval) {
     // Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED ){ 
      auid = httpGETRequest(serverName);
      Serial.println(auid);
      JSONVar myObject = JSON.parse(auid);
      // Serial.println(myObject);
      // JSON.typeof(jsonVar) can be used to get the type of the var
      if (JSON.typeof(myObject) == "undefined") {
        Serial.println("Parsing input failed!");
        return;
      }
    
      Serial.print("JSON object = ");
      Serial.println(myObject);
    
      // myObject.keys() can be used to get an array of all the keys in the object
      keys = myObject;

      for (int i = 0; i < keys.length(); i++) {
          JSONVar value = keys[i];
          Serial.println(value);
      }

      // save the last HTTP GET Request
      previousMillis = currentMillis;
    }
    else {
      Serial.println("WiFi Disconnected");
    }
  }
  // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
  if (!mfrc522.PICC_IsNewCardPresent()) {
      return;
  }
  

  // Select one of the cards
  if (!mfrc522.PICC_ReadCardSerial()) {
      return;
  }

  

  // Get the UID
  String uid = "";
  for (byte i = 0; i < mfrc522.uid.size; ++i) {
      uid += String(mfrc522.uid.uidByte[i], HEX);
  }
  Serial.print("Le UID est: ");
  Serial.println(uid);
  for (int i = 0; i < keys.length(); i++) {
    // const char* uidverif = "";
    JSONVar value = keys[i];
    String uidverif = value;
    // supprimerPremierEtDernierCaractere(String &maChaine)
    // Serial.println(uidverif);
    // Compare the UID with the known value
    if (uid == uidverif) { // Remplacez cette valeur par l'UID attendu
        // Accès autorisé
        // Serial.print(keys.length());
        digitalWrite(greenPin, HIGH); // Allumer la LED verte
        digitalWrite(redPin, LOW);     // Éteindre la LED rouge
        Serial.println("Accès autorisé");
        badgegood = 1;
        Serial.println(badgegood);
        delay(4000);
        digitalWrite(greenPin, LOW);  // Éteindre la LED verte
        digitalWrite(redPin, LOW);   // Allumer la LED rouge
    } 
  }
  Serial.println(badgegood);
  if (badgegood == 0){
    // Accès refusé
    digitalWrite(greenPin, LOW); // Allumer la LED verte
    digitalWrite(redPin, HIGH);     // Éteindre la LED rouge
    Serial.println("Accès refusé, badge inconnu");
    delay(4000);
    digitalWrite(greenPin, LOW);  // Éteindre la LED verte
    digitalWrite(redPin, LOW);   // Allumer la LED rouge
  }
  badgegood = 0;

  // Attendre un peu avant de vérifier à nouveau (ajustez selon vos besoins)
    // delay(1000);

    // Afficher les détails de la carte
    //mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
}

// Fonction pour supprimer le premier et le dernier caractère d'une variable de type String
void supprimerPremierEtDernierCaractere(String &maChaine) {
  maChaine = maChaine.substring(1, maChaine.length() - 1);
}

String httpGETRequest(const char* serverName) {
  WiFiClientSecure *client = new WiFiClientSecure;
  
  // set secure client without certificate
  client->setInsecure();
  HTTPClient https;
    
  // Your IP address with path or Domain name with URL path 
  https.begin(*client, serverName);
  
  // Send HTTP POST request
  int httpResponseCode = https.GET();
  
  String payload = "{}"; 
  
  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = https.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  https.end();

  return payload;
}


