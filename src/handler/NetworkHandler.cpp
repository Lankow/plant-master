/*
*   NetworkHandler.cpp
*   ----------------------
*   Created on: 2023/09/26
*   Author: Lankow
*/
#include "handler/NetworkHandler.hpp"
#include "config.h"
#include "constants.hpp"
#include "DataProvider.hpp"

AsyncWebServer m_server(80);

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
  startServer();
};

void NetworkHandler::updateTimeViaNTP(){
  if(WiFi.status() == WL_CONNECTED){
    configTime(GMT_OFFSET, DAY_OFFSET, NTP_SERVER_PL_0, NTP_SERVER_PL_1, NTP_SERVER_PL_2);
  }
  else{
    Serial.println("WiFi connection not available - Time update is not possible...");
  }
};

void NetworkHandler::startServer(){
  if(NULL != &m_server){
    m_server.on("/humidity", HTTP_GET, [this](AsyncWebServerRequest *request){
      int humidityData = getDataProvider()->getHumidity();
      String response = String(humidityData);
      request->send(200, "text/html", response);
    });

    m_server.on("/threshold", HTTP_POST, [this](AsyncWebServerRequest * request) 
    {
      int paramsNr = request->params();
      AsyncWebParameter * param = request->getParam(0);
      int threshold = param->value().toInt();

      Serial.printf("Threshold to set: %d \n", threshold);
      getDataProvider()->setThreshold(param->value().toInt());

      request->send(200);
  });

  m_server.begin();
  }
};