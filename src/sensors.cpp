#include <Arduino.h>
#include <DHT.h>

#include "sensors.h"
#include "config.h"

DHT dht(DHTPIN, DHT22);

bool lastMotion = LOW;

void setupSensors() {

    pinMode(PIR, INPUT);

    dht.begin();
}

void readSensors() {

    float t = dht.readTemperature();
    float h = dht.readHumidity();

    if (!isnan(t) && !isnan(h)) {

        Serial.print("Temperature: ");
        Serial.println(t);

        Serial.print("Humidity: ");
        Serial.println(h);
    }

    bool currentMotion = digitalRead(PIR);

    if (currentMotion != lastMotion) {

        lastMotion = currentMotion;

        if (currentMotion == HIGH) {

            Serial.println("Motion Detected");

        } else {

            Serial.println("No Motion");
        }
    }
}