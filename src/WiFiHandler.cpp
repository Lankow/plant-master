/*
*   WiFiHandler.cpp
*   ----------------------
*   Created on: 2023/09/26
*   Author: Lankow
*/
#include "WiFiHandler.h"
#include "config.h"

WiFiHandler::WiFiHandler(){};

void WiFiHandler::initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
};
