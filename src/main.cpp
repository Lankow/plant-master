#include <Arduino.h>
#include <WiFi.h>
#include "config.h"

#define LED_BUILTIN 2

const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;

WiFiServer server(80);

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(921600);
  Serial.println("Setup");
}

void loop() {
  delay(1000);
  Serial.println("Loop");
}
