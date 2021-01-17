# 5Fach-Touch-Wandtaster-MQTT
5Fach Wandtaster mit Toch Funktion, Temperaturmessung und Nachtlicht, Steuerung über MQTT

## # Projekt ist aktuell noch im Aufbau! Ziel ist es, einen 5-Fach Touch Wandtaster mit verschiedenen fuktionen zu erstellen. Angelehnt an dem [Glastaster von Loxone](https://shop.loxone.com/dede/touch-pure-tree-weiss.html). 
_Das ganze ist auch mein erstes Projekt was Arduino Sketche schreiben angeht, da wird sicher noch viel potenzial drinnen sein zwecks Optimierung_

Aktueller Stand: 17.01.2020
* WiFi Einbindung
* MQTT Einbindung
* Einbindung der Doppelklick funktion mittels [OneButton](https://github.com/mathertel/OneButton)
* 1-Wire Einbindung für DS18B20 Temperaturmessung
* Einbundung der Nachtlicht LED

Das ganze läuft (aktuell) auf einem WeMos D1 mini.
Die Touchfunktionen sollen zum Test Anfangs mit 5 TTP223 Modulen gelöst werden, welche hinter einer 3mm Acryl-/Plexiglasplatte in weiß (natürlich auch jede andere Farbe möglich) geklebt werden. Jede Tochfläche hat aktuell 4 Schaltmöglichkeiten, macht bei 5 Flächen als 20 möglichkeiten.
* kurzer klick
* doppel (2x) klick
* langer (gedrückter) klick
* sowie nach loslassen 

