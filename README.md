# 5Fach-Touch-Wandtaster-MQTT
5Fach Touchtaster mit Status-LED/Orientierungslicht, gesteuert über MQTT

## # Projekt ist aktuell noch im Aufbau! Ziel ist es, einen 5-Fach Touch Wandtaster mit verschiedenen fuktionen zu erstellen. Angelehnt an dem [Glastaster von Loxone](https://shop.loxone.com/dede/touch-pure-tree-weiss.html). 
_Das ganze ist auch mein erstes Projekt was Arduino Sketche schreiben angeht, da wird sicher noch viel potenzial drinnen sein zwecks Optimierung_


Das ganze läuft (aktuell) auf einem WeMos D1 mini.
Die Berührungen werden von einem MPR121 und Kupferflächen, geklebt auf eine Wippe von der Busch-Jaeger Future Linea Serie. 
In den Dateien sind auch stl Druck Dateien dabei. Mit diesen lassen sich zum einen die Wippe im Rahmen etwas "herausstellen" sowie der eigentlich Rahmen auf eine Hohlwanddose / Unterputzdose verschrauben. 
Bei mir sitzt in der unterputzdose ein 5V Netzteil welches den WeMos versorgt.

Die Daten der Berührung werden per MQTT an NodeRed gesendet und dort ausgewertet, wie oft welche Fläche berührt wurde. An Hand dessen lassen sich dann die Aktionen verknüpfen. Entweder direkt in NodeRed an die Endgeräte oder auch über MQTT versenden.

Die Status LED leuchtet bei jeder Berührung grün und nach kurzer Zeit des Los lassen's wird diese blau. Die Farben lassen sich auch einstellen. Auch das läuft über MQTT.

Das NodeRed Skript wertet aktuell 1,2 und 3 Klicks / Berührungen aus, lässt sich aber beliebig erweitern. 

Video zum Projekt: https://youtu.be/CV--ynpiq84

To-Do:
- Teileliste beifügen
