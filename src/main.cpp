#include <Arduino.h>

#include "config.h"
#include "leds.h"
#include "mqtt.h"
#include "sensors.h"

void setup() {

  Serial.begin(115200);

  setupLEDs();
  setupSensors();
  setupMQTT();

}

void loop() {

  mqttLoop();

  updateLEDs();

  readSensors();

  delay(100);

}