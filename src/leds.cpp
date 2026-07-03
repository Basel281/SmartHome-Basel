#include <Arduino.h>
#include "leds.h"
#include "config.h"
#include "mqtt.h"

// Zentraler Zustand von LED1, damit Taster und MQTT-Befehle konsistent bleiben
bool led1State = false;

// Entprellung (Debouncing) fuer den Taster
int lastButtonReading = HIGH;
bool debouncedButtonState = HIGH;
unsigned long lastDebounceTime = 0;
const unsigned long DEBOUNCE_DELAY = 50;

void setupLEDs() {
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(LED3, OUTPUT);

    pinMode(BUTTON, INPUT_PULLUP);

    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
}

// Zentrale Funktion zum Setzen von LED1 -- wird sowohl vom Taster
// als auch von eingehenden MQTT-Nachrichten (LED1_TOPIC) verwendet,
// damit der physische Zustand und der MQTT-Zustand nie auseinanderlaufen.
void setLED1(bool state) {
    led1State = state;
    digitalWrite(LED1, led1State ? HIGH : LOW);
}

// Liest den Taster entprellt aus und schaltet LED1 lokal um (Lichtschalter-Funktion).
// Der neue Zustand wird zusaetzlich per MQTT publiziert, damit das Dashboard
// den manuellen Tastendruck sofort mitbekommt.
void updateLEDs() {

    int reading = digitalRead(BUTTON);

    if (reading != lastButtonReading) {
        lastDebounceTime = millis();
    }

    if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY) {

        if (reading != debouncedButtonState) {

            debouncedButtonState = reading;

            // BUTTON ist mit INPUT_PULLUP verdrahtet: gedrueckt = LOW
            if (debouncedButtonState == LOW) {

                setLED1(!led1State);

                client.publish(LED1_TOPIC, led1State ? "ON" : "OFF");
            }
        }
    }

    lastButtonReading = reading;
}
