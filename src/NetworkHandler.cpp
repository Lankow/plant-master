/*
*   NetworkHandler.cpp
*   ----------------------
*   Created on: 2023/09/26
*   Author: Lankow
*/
#include "NetworkHandler.h"
#include "config.h"
#include "constants.h"

NetworkHandler::NetworkHandler(){};

void NetworkHandler::initWiFi() {
  uint8_t connectionCounter = 0;

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.printf("Connecting to SSID: %s \n", WIFI_SSID);
  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);

    connectionCounter++;

    if(connectionCounter >= MAX_CONNECTION_TRIES){
      Serial.println("Encountered error when connecting to WiFi... \n");
      return;
    }
  }

  IPAddress ip = WiFi.localIP();

  Serial.printf("WiFi Connected - IP Address: %u.%u.%u.%u \n", ip[0], ip[1], ip[2], ip[3]);
  updateTimeViaNTP();
};

void NetworkHandler::updateTimeViaNTP(){
  if(WiFi.status() == WL_CONNECTED){
    configTime(GMT_OFFSET, DAY_OFFSET, NTP_SERVER_PL_0, NTP_SERVER_PL_1, NTP_SERVER_PL_2);
  }
  else{
    Serial.println("WiFi connection not available - Time update is not possible...");
  }
};


