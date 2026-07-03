# SmartHome-Basel

ESP32-Firmware für den berührungslos steuerbaren Smart-Home-Prototyp (Teil B: ESP32, Sensoren, Aktoren, MQTT).
Teil des Projekts **Smart-Home-Steuerung** (Klasse ETS1_26_P1, Projektzeitraum 16.06. – 07.07.2026).

## Funktionsübersicht

- **3× LED** als Aktoren, steuerbar per MQTT (`ON`/`OFF`) und – für LED1 zusätzlich – per physischem Taster
- **DHT22-Sensor**: misst Temperatur und Luftfeuchtigkeit und publiziert die Werte periodisch per MQTT
- **PIR-Bewegungsmelder**: erkennt Bewegung und meldet Zustandswechsel per MQTT
- **Taster**: schaltet LED1 lokal um (Lichtschalter-Funktion); der neue Zustand wird per MQTT publiziert, damit das Dashboard synchron bleibt
- **WiFi + MQTT**: verbindet sich beim Start automatisch mit dem WLAN und dem öffentlichen MQTT-Broker `broker.hivemq.com`

## Hardware / Pinbelegung

| Komponente         | Pin (ESP32) |
|---------------------|:-----------:|
| LED 1                | GPIO 25     |
| LED 2                | GPIO 26     |
| LED 3                | GPIO 27     |
| Taster (Button)      | GPIO 4      |
| PIR-Bewegungsmelder   | GPIO 14     |
| DHT22 (Temp./Feuchte) | GPIO 15     |

Der Taster ist als `INPUT_PULLUP` konfiguriert und schaltet gegen GND – es wird kein externer Pull-up-Widerstand benötigt.

Die vollständige Schaltung ist in [`diagram.json`](diagram.json) hinterlegt und kann direkt in [Wokwi](https://wokwi.com/) simuliert werden.

## MQTT-Topics

Broker: `broker.hivemq.com` (Port 1883, öffentlich, unverschlüsselt)

| Topic                          | Richtung        | Werte         | Beschreibung                        |
|---------------------------------|------------------|---------------|--------------------------------------|
| `basel/smarthome/led1`          | Subscribe/Publish| `ON` / `OFF`  | LED 1 schalten (MQTT und Taster)     |
| `basel/smarthome/led2`          | Subscribe        | `ON` / `OFF`  | LED 2 schalten                       |
| `basel/smarthome/led3`          | Subscribe        | `ON` / `OFF`  | LED 3 schalten                       |
| `basel/smarthome/temperature`   | Publish          | Fließkommazahl| Temperatur in °C, bei jeder gültigen Messung |
| `basel/smarthome/humidity`      | Publish          | Fließkommazahl| Luftfeuchtigkeit in %, bei jeder gültigen Messung |
| `basel/smarthome/motion`        | Publish          | `1` / `0`     | Bewegung erkannt / keine Bewegung, bei Zustandswechsel |

## Projektstruktur

```
SmartHome_Basel/
├── src/
│   ├── main.cpp      # Einstiegspunkt: setup()/loop()
│   ├── mqtt.cpp       # WiFi-Verbindung, MQTT-Client, eingehende Befehle
│   ├── sensors.cpp    # DHT22- und PIR-Auswertung, Publizieren der Messwerte
│   └── leds.cpp       # LED-Ansteuerung, Taster-Entprellung und lokale Umschaltung
├── include/
│   ├── config.h       # WLAN-Zugangsdaten, MQTT-Topics, Pinbelegung
│   ├── mqtt.h
│   ├── sensors.h
│   └── leds.h
├── diagram.json        # Wokwi-Schaltplan
└── platformio.ini      # Build-Konfiguration (ESP32, Arduino-Framework)
```

## Verwendete Bibliotheken

- [PubSubClient](https://github.com/knolleary/pubsubclient) – MQTT-Kommunikation
- [DHT sensor library](https://github.com/adafruit/DHT-sensor-library) (Adafruit) – Auslesen des DHT22
- [Adafruit Unified Sensor](https://github.com/adafruit/Adafruit_Sensor) – Abhängigkeit der DHT-Bibliothek

## Build & Simulation

1. Projekt in VS Code mit installierter [PlatformIO](https://platformio.org/)-Extension öffnen
2. `pio run` zum Kompilieren ausführen
3. `diagram.json` in Wokwi öffnen, um die Schaltung zu simulieren
4. WLAN-Zugangsdaten und MQTT-Server bei Bedarf in `include/config.h` anpassen

## Bekannte Einschränkungen

- Der öffentliche MQTT-Broker (`broker.hivemq.com`) ist unauthentifiziert und unverschlüsselt – für den Prototyp im Unterrichtskontext akzeptabel, für einen Produktiveinsatz ungeeignet
- LED2 und LED3 können ausschließlich per MQTT gesteuert werden, nicht per Taster (nur LED1 hat eine lokale Bedienung)
