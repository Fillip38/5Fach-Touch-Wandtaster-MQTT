//Version 2.0 01/2021
//Toucherkennung mittels MPR121
//Fillip Goerbing - www.LauLip.de

#include <MPR121.h>
#include <MPR121_Datastream.h>
#include <Wire.h>
#include "OneButton.h"
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define numElectrodes 5                // Anzahl Touchpunkte
#define NightLED      D7                 // Nachtlicht LED Pin


const uint32_t BAUD_RATE = 9600;  
const uint8_t MPR121_ADDR = 0x5A;
const uint8_t MPR121_INT = D3;        //IRQ Pin
const bool MPR121_DATASTREAM_ENABLE = false;

const char* SSID = "SSID";
const char* PSK = "PASSWORD";
const char* MQTT_BROKER = "BROKER_IP";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];

/**********************************************(Setup)********************************************/
void setup () {
  Serial.begin (9600);

  pinMode(NightLED,OUTPUT);
 
  MPR121.begin(0x5a);             // MPR121 Kapazitiv Touch mit Adresse 0x5a initialisieren
  MPR121.setInterruptPin(D3);      // MPR121 Kapazitiv Touch Interrupt Pin definieren
  MPR121.setTouchThreshold(25);   // Schwellwert erkennen von Berührung
  MPR121.setReleaseThreshold(20); // Schwellwert erkennen loslassen, muss kleiner sein als Berührung
  MPR121.updateTouchData();       // Touch Daten aktualisieren
 
  setup_wifi();
  client.setServer(MQTT_BROKER, 1882);
  client.setCallback(callback);
}


void setup_wifi() {
    delay(10);
    Serial.println();
    Serial.print("Verbinde zu ");
    Serial.println(SSID);
 
    WiFi.begin(SSID, PSK);
 
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
 
    Serial.println("");
    Serial.print("Erfolgreich verbunden mit ");
    Serial.println(SSID);
    Serial.print("IP Adresse: ");
    Serial.println(WiFi.localIP());

    }


void reconnect() {
    while (!client.connected()) {
        Serial.println("Verbinde MQTT Server...");
        if (!client.connect("KZ_TouchTaster")) {
            Serial.print("MQTT Verbindung nicht moeglich=");
            Serial.print(client.state());
            Serial.println(" versuche erneut in 5 sekunden");
            notready();
            delay(5000);
        }
    }
    client.subscribe("/SmartHome/EG/Kinderzimmer/Touchtaster/LED");
    Serial.println("MQTT Server verbunden...");


    Serial.print("MQTT FullTopic = " );
    Serial.println("/SmartHome/EG/Kinderzimmer/Touchtaster");
    ready();
}


void callback(char* topic, byte* payload, unsigned int length) {
    Serial.print("Empfangene Nachricht [");
    Serial.print(topic);
    Serial.print("] ");
    char msg[length+1];
    for (int i = 0; i < length; i++) {
        Serial.print((char)payload[i]);
        msg[i] = (char)payload[i];
    }
    Serial.println();
 
    msg[length] = '\0';
    Serial.println(msg);

       
        if(strcmp(msg,"on")==0){
        digitalWrite(NightLED, HIGH);
    }
    else if(strcmp(msg,"off")==0){
        digitalWrite(NightLED, LOW);
    } 
 
   
}

/*****************************************(Hauptprogramm)*****************************************/
void loop () {
    if (!client.connected()) {
    reconnect();
    }
    client.loop();
    MPR121.updateAll();
    

    if (MPR121.isNewTouch(0)) {
      Serial.println("Button 0 pressed ");
      client.publish("/SmartHome/EG/Kinderzimmer/Touchtaster/0", "1");
      } else if (MPR121.isNewRelease(0)) {
      Serial.println("Button 0 released ");
      client.publish("/SmartHome/EG/Kinderzimmer/Touchtaster/0", "0");
    }

    if (MPR121.isNewTouch(1)) {
      Serial.println("Button 1 pressed ");
      client.publish("/SmartHome/EG/Kinderzimmer/Touchtaster/1", "1");
      } else if (MPR121.isNewRelease(1)) {
      Serial.println("Button 1 released ");
      client.publish("/SmartHome/EG/Kinderzimmer/Touchtaster/1", "0");
    }

    if (MPR121.isNewTouch(2)) {
      Serial.println("Button 2 pressed ");
      client.publish("/SmartHome/EG/Kinderzimmer/Touchtaster/2", "1");
      } else if (MPR121.isNewRelease(2)) {
      Serial.println("Button 2 released ");
      client.publish("/SmartHome/EG/Kinderzimmer/Touchtaster/2", "0");
    }

    if (MPR121.isNewTouch(3)) {
      Serial.println("Button 3 pressed ");
      client.publish("/SmartHome/EG/Kinderzimmer/Touchtaster/3", "1");
      } else if (MPR121.isNewRelease(3)) {
      Serial.println("Button 3 released ");
      client.publish("/SmartHome/EG/Kinderzimmer/Touchtaster/3", "0");
    }

    if (MPR121.isNewTouch(4)) {
      Serial.println("Button 4 pressed ");
      client.publish("/SmartHome/EG/Kinderzimmer/Touchtaster/4", "1");
      } else if (MPR121.isNewRelease(4)) {
      Serial.println("Button 4 released ");
      client.publish("/SmartHome/EG/Kinderzimmer/Touchtaster/4", "0");
    }     
}

void notready() {
    digitalWrite(NightLED, HIGH);
    delay(100);
    digitalWrite(NightLED, LOW);
    delay(100);
    digitalWrite(NightLED, HIGH);
    delay(100);
    digitalWrite(NightLED, LOW);
}

void ready() {
    digitalWrite(NightLED, HIGH);
    delay(250);
    digitalWrite(NightLED, LOW);
    delay(250);
    digitalWrite(NightLED, HIGH);
    delay(250);
    digitalWrite(NightLED, LOW);
    delay(250);
    digitalWrite(NightLED, HIGH);
    delay(250);
    digitalWrite(NightLED, LOW);
    Serial.println("Initzialisierung abgeschlossen");
    client.publish("/SmartHome/EG/Kinderzimmer/Touchtaster/Initzialisierung", "abgeschlossen");
}
