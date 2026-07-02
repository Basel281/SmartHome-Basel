#include <Arduino.h>
#include "leds.h"
#include "config.h"

void setupLEDs() {
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(LED3, OUTPUT);

    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
}

void updateLEDs() {

}