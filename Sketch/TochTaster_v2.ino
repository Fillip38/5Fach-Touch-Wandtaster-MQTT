//Version 2.0 05.02.2121 - Einbindung der WS2812B LED und optischer Tastberuehrung
//Toucherkennung mittels MPR121
//Fillip Goerbing - www.LauLip.de

#include <MPR121.h>
#include <MPR121_Datastream.h>
#include <Wire.h>
#include "OneButton.h"
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Adafruit_NeoPixel.h>

#define numElectrodes 5                // Anzahl Touchpunkte
#define LEDPIN        D5
#define NUMPIXELS     1


const uint32_t BAUD_RATE = 9600;  
const uint8_t MPR121_ADDR = 0x5A;
const uint8_t MPR121_INT = D3;        //IRQ Pin
const bool MPR121_DATASTREAM_ENABLE = false;

const char* SSID = "SSID";
const char* PSK = "PASSWORD";
const char* MQTT_BROKER = "MQTT_SERVER_IP";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, LEDPIN, NEO_GRB + NEO_KHZ800);
int delayval = 500;
/**********************************************(Setup)********************************************/
void setup () {
  Serial.begin (9600);
  Serial.println("TouchTaster v2.0");

  MPR121.begin(0x5a);             // MPR121 Kapazitiv Touch mit Adresse 0x5a initialisieren
  MPR121.setInterruptPin(D3);      // MPR121 Kapazitiv Touch Interrupt Pin definieren
  MPR121.setTouchThreshold(25);   // Schwellwert erkennen von Berührung
  MPR121.setReleaseThreshold(20); // Schwellwert erkennen loslassen, muss kleiner sein als Berührung
  MPR121.updateTouchData();       // Touch Daten aktualisieren

  pixels.begin();                 // Initialisierung der NeoPixel
 
  setup_wifi();
  client.setServer(MQTT_BROKER, 1883);
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
            delay(5000);
        }
    }
    client.subscribe("/SmartHome/EG/Kinderzimmer/Touchtaster/StatusLED/#");
    Serial.println("MQTT Server verbunden...");


    Serial.print("MQTT FullTopic = " );
    Serial.println("/SmartHome/EG/Kinderzimmer/Touchtaster");
    ready();
}


void callback(char* topic, byte* payload, unsigned int length) {
  String sTopic = String(topic);

  Serial.print("Empfange Topic: ");
  Serial.println(sTopic);

  payload[length] = '\0';
  String sValue = String((char*)payload);

  Serial.print("Empfange Wert: ");
  Serial.println(sValue);

  long number = (long)strtol(&sValue[0], NULL, 16);
  int r = number >> 16;
  int g = number >> 8 & 0xFF;
  int b = number & 0xFF;

  Serial.print("Rot: ");
  Serial.println(r);
  Serial.print("Gruen: ");
  Serial.println(g);
  Serial.print("Blau: ");
  Serial.println(b);

  pixels.setPixelColor(0, pixels.Color(r, g, b));
  pixels.show();
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
      client.publish("/SmartHome/EG/Kinderzimmer/Touchtaster/0", "true");
      pressed();
      } else if (MPR121.isNewRelease(0)) {
      Serial.println("Button 0 released ");
    //  client.publish("/SmartHome/EG/Kinderzimmer/Touchtaster/0", "false");
      released();
    }

    if (MPR121.isNewTouch(1)) {
      Serial.println("Button 1 pressed ");
      client.publish("/SmartHome/EG/Kinderzimmer/Touchtaster/1", "true");
      pressed();
      } else if (MPR121.isNewRelease(1)) {
      Serial.println("Button 1 released ");
    //  client.publish("/SmartHome/EG/Kinderzimmer/Touchtaster/1", "false");
      released();
    }

    if (MPR121.isNewTouch(2)) {
      Serial.println("Button 2 pressed ");
      client.publish("/SmartHome/EG/Kinderzimmer/Touchtaster/2", "true");
      pressed();
      } else if (MPR121.isNewRelease(2)) {
      Serial.println("Button 2 released ");
    //  client.publish("/SmartHome/EG/Kinderzimmer/Touchtaster/2", "false");
      released();
    }

    if (MPR121.isNewTouch(3)) {
      Serial.println("Button 3 pressed ");
      client.publish("/SmartHome/EG/Kinderzimmer/Touchtaster/3", "true");
      pressed();
      } else if (MPR121.isNewRelease(3)) {
      Serial.println("Button 3 released ");
    //  client.publish("/SmartHome/EG/Kinderzimmer/Touchtaster/3", "false");
      released();
    }

    if (MPR121.isNewTouch(4)) {
      Serial.println("Button 4 pressed ");
      client.publish("/SmartHome/EG/Kinderzimmer/Touchtaster/4", "true");
      pressed();
      } else if (MPR121.isNewRelease(4)) {
      Serial.println("Button 4 released ");
    //  client.publish("/SmartHome/EG/Kinderzimmer/Touchtaster/4", "false");
     released();
    }     
}

void ready() {
    Serial.println("Initzialisierung abgeschlossen");
    pixels.setPixelColor(0, pixels.Color(10,0,0));  
    pixels.show();                                    
   // client.publish("/SmartHome/EG/Kinderzimmer/Touchtaster/Initzialisierung", "abgeschlossen");
}

void pressed() {
    pixels.setPixelColor(0, pixels.Color(0,75,0));  
    pixels.show();
}

void released() {
    pixels.setPixelColor(0, pixels.Color(0,0,0));  
    pixels.show();
}
