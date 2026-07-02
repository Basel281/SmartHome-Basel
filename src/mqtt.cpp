#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

#include "mqtt.h"
#include "config.h"

WiFiClient espClient;
PubSubClient client(espClient);
void setupMQTT() {

    client.setServer(MQTT_SERVER, 1883);
    client.setCallback(mqttCallback);

}
void mqttCallback(char* topic, byte* payload, unsigned int length) {

  String message = "";

  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }

  Serial.print("Topic: ");
  Serial.println(topic);

  Serial.print("Message: ");
  Serial.println(message);

  if (String(topic) == LED1_TOPIC) {
    digitalWrite(LED1, message == "ON");
  }

  if (String(topic) == LED2_TOPIC) {
    digitalWrite(LED2, message == "ON");
  }

  if (String(topic) == LED3_TOPIC) {
    digitalWrite(LED3, message == "ON");
  }
}
void reconnectMQTT() {

  while (!client.connected()) {

    Serial.print("Connecting MQTT...");

    if (client.connect("ESP32_Basel")) {

      Serial.println(" Connected");

      client.subscribe(LED1_TOPIC);
      client.subscribe(LED2_TOPIC);
      client.subscribe(LED3_TOPIC);

    } else {

      Serial.print(" Failed, rc=");
      Serial.println(client.state());

      delay(2000);
    }
  }
}
void mqttLoop() {

  if (!client.connected()) {
    reconnectMQTT();
  }

  client.loop();
}