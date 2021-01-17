//Sketch fuer 5-fach Wandtaster mit Temperaturmessung und Orientierungslicht. Gesteuert ueber MQTT
//Doppelklick funktion hinzugefuegt per OneButton.h - https://github.com/mathertel/OneButton
//Temperaturmessung mit MQTT Versand noch nicht nicht komplett 
//OrientiergunsLED ueber MQTT schaltbar
#include "OneButton.h"
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define NightLED D0
#define ONE_WIRE_BUS D3
#define HelligkeitsSensor A0

OneButton button1(D1, false);
OneButton button2(D2, false);
OneButton button3(D5, false);
OneButton button4(D6, false);
OneButton button5(D7, false);


OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

const char* SSID = "SSID";
const char* PSK = "Password";
const char* MQTT_BROKER = "MQTT_IP";


WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];

int value = 0;
int sensorWert = 0;

void setup()
{
pinMode(NightLED, OUTPUT);

    Serial.begin(115200);
    setup_wifi();
    client.setServer(MQTT_BROKER, 1882);
    client.setCallback(callback);
    sensors.begin();

  button1.attachClick(click1);
  button1.attachDoubleClick(doubleclick1);
  button1.attachLongPressStop(longPressStop1);
  button1.attachDuringLongPress(longPress1);

  button2.attachClick(click2);
  button2.attachDoubleClick(doubleclick2);
  button2.attachLongPressStop(longPressStop2);
  button2.attachDuringLongPress(longPress2);

  button3.attachClick(click3);
  button3.attachDoubleClick(doubleclick3);
  button3.attachLongPressStop(longPressStop3);
  button3.attachDuringLongPress(longPress3);

  button4.attachClick(click4);
  button4.attachDoubleClick(doubleclick4);
  button4.attachLongPressStop(longPressStop4);
  button4.attachDuringLongPress(longPress4);

  button5.attachClick(click5);
  button5.attachDoubleClick(doubleclick5);
  button5.attachLongPressStop(longPressStop5);
  button5.attachDuringLongPress(longPress5);
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
    Serial.println("WiFi verbunden");
    Serial.println("IP Adresse: ");
    Serial.println(WiFi.localIP());
}


void reconnect() {
    while (!client.connected()) {
        Serial.println("Verbinde MQTT Server...");
        if (!client.connect("ESP8266Client")) {
            Serial.print("MQTT Verbindung nicht moeglich=");
            Serial.print(client.state());
            Serial.println(" versuche erneut in 5 sekunden");
            digitalWrite(NightLED, HIGH);
            delay(100);
            digitalWrite(NightLED, LOW);
            delay(100);
            digitalWrite(NightLED, HIGH);
            delay(100);
            digitalWrite(NightLED, LOW);
            delay(5000);
        }
    }
    client.subscribe("/home/data");
    Serial.println("MQTT Server verbunden...");
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
        client.publish("/home/touchtaster/LED", "on");
    }
    else if(strcmp(msg,"off")==0){
        digitalWrite(NightLED, LOW);
        client.publish("/home/touchtaster/LED", "off");
    }
}

void loop()
{
      if (!client.connected()) {
        reconnect();
    }
    client.loop();
  button1.tick();
  button2.tick();
  button3.tick();
  button4.tick();
  button5.tick();
  delay(10);
  
 sensor();
}


// click1
void click1() {
  Serial.println("Button 1 click.");
  client.publish("/home/touchtaster/1", "1");
  delay(500);
  client.publish("/home/touchtaster/1", "0");
} 

// doubleclick1
void doubleclick1() {
  Serial.println("Button 1 doubleclick.");
  client.publish("/home/touchtaster/1", "2");
  delay(500);
  client.publish("/home/touchtaster/1", "0");
} 

// longPress1
void longPress1() {
  Serial.println("Button 1 longPress...");
  client.publish("/home/touchtaster/1", "3");
  delay(500);
  client.publish("/home/touchtaster/1", "0");
} 

// longPressStop1
void longPressStop1() {
  Serial.println("Button 1 longPress stop");
  client.publish("/home/touchtaster/1", "4");
  delay(500);
  client.publish("/home/touchtaster/1", "0");
} 


// click2
void click2() {
  Serial.println("Button 2 click.");
  client.publish("/home/touchtaster/2", "1");
  delay(500);
  client.publish("/home/touchtaster/2", "0");
} 

// doubleclick2
void doubleclick2() {
  Serial.println("Button 2 doubleclick.");
  client.publish("/home/touchtaster/2", "2");
  delay(500);
  client.publish("/home/touchtaster/2", "0");
} 

// longPress2
void longPress2() {
  Serial.println("Button 2 longPress...");
  client.publish("/home/touchtaster/2", "3");
  delay(500);
  client.publish("/home/touchtaster/2", "0");
} 

// longPressStop2
void longPressStop2() {
  Serial.println("Button 2 longPress stop");
  client.publish("/home/touchtaster/2", "4");
  delay(500);
  client.publish("/home/touchtaster/2", "0");
}

// click3
void click3() {
  Serial.println("Button 3 click.");
  client.publish("/home/touchtaster/3", "1");
  delay(500);
  client.publish("/home/touchtaster/3", "0");
} 

// doubleclick3
void doubleclick3() {
  Serial.println("Button 3 doubleclick.");
  client.publish("/home/touchtaster/3", "2");
  delay(500);
  client.publish("/home/touchtaster/3", "0");
} 

// longPress3
void longPress3() {
  Serial.println("Button 3 longPress...");
  client.publish("/home/touchtaster/3", "3");
  delay(500);
  client.publish("/home/touchtaster/3", "0");
} 

// longPressStop3
void longPressStop3() {
  Serial.println("Button 3 longPress stop");
  client.publish("/home/touchtaster/3", "4");
  delay(500);
  client.publish("/home/touchtaster/3", "0");
}

// click4
void click4() {
  Serial.println("Button 4 click.");
  client.publish("/home/touchtaster/4", "1");
  delay(500);
  client.publish("/home/touchtaster/4", "0");
} 

// doubleclick4
void doubleclick4() {
  Serial.println("Button 4 doubleclick.");
  client.publish("/home/touchtaster/4", "2");
  delay(500);
  client.publish("/home/touchtaster/4", "0");
} 

// longPress4
void longPress4() {
  Serial.println("Button 4 longPress...");
  client.publish("/home/touchtaster/4", "3");
  delay(500);
  client.publish("/home/touchtaster/4", "0");
} 

// longPressStop4
void longPressStop4() {
  Serial.println("Button 4 longPress stop");
  client.publish("/home/touchtaster/4", "4");
  delay(500);
  client.publish("/home/touchtaster/4", "0");
}

// click5
void click5() {
  Serial.println("Button 5 click.");
  client.publish("/home/touchtaster/5", "1");
  delay(500);
  client.publish("/home/touchtaster/5", "0");
} 

// doubleclick5
void doubleclick5() {
  Serial.println("Button 5 doubleclick.");
  client.publish("/home/touchtaster/5", "2");
  delay(500);
  client.publish("/home/touchtaster/5", "0");
} 

// longPress5
void longPress5() {
  Serial.println("Button 5 longPress...");
  client.publish("/home/touchtaster/5", "3");
  delay(500);
  client.publish("/home/touchtaster/5", "0");
} 

// longPressStop5
void longPressStop5() {
  Serial.println("Button 5 longPress stop");
  client.publish("/home/touchtaster/5", "4");
  delay(500);
  client.publish("/home/touchtaster/5", "0");
}

//Sensordaten abfragen
void sensor()
{
  sensorWert =analogRead(HelligkeitsSensor);
  Serial.print("Sensorwert = " );
  Serial.println(sensorWert); 
  
  sensors.requestTemperatures();
  Serial.println("Temperature is: " + String(sensors.getTempCByIndex(0)) + "°C");
 }
