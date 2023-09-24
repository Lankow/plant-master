#include <Arduino.h>
#include <WiFi.h>
#include "config.h"

#define LED_BUILTIN 2

const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;

WiFiServer server(80);

void initWiFi();

void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(921600);
  Serial.println("Setup");
  // initWiFi();
}

void loop() {
  delay(1000);
  Serial.println("Loop");
  Serial.println(analogRead(34));
}
