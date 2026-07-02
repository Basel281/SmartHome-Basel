#ifndef CONFIG_H
#define CONFIG_H

// WiFi
#define WIFI_SSID "Wokwi-GUEST"
#define WIFI_PASSWORD ""

// MQTT
#define MQTT_SERVER "broker.hivemq.com"

// Topics
#define LED1_TOPIC "basel/smarthome/led1"
#define LED2_TOPIC "basel/smarthome/led2"
#define LED3_TOPIC "basel/smarthome/led3"

#define TEMP_TOPIC "basel/smarthome/temperature"
#define HUM_TOPIC "basel/smarthome/humidity"
#define MOTION_TOPIC "basel/smarthome/motion"

// Pins
#define LED1 25
#define LED2 26
#define LED3 27

#define BUTTON 4
#define PIR 14

#define DHTPIN 15

#endif