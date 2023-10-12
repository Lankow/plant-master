/*
*   NetworkManager.cpp
*   ----------------------
*   Created on: 2023/09/26
*   Author: Lankow
*/
#include "manager/NetworkManager.hpp"
#include "config.hpp"
#include "constants.hpp"

AsyncWebServer m_server(80);

void NetworkManager::init() {
  uint8_t connectionCounter = 0;

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.printf("Connecting to SSID: %s \n", WIFI_SSID);
  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);

    connectionCounter++;

    if(connectionCounter >= MAX_CONNECTION_TRIES){
      Logger::log("Encountered error when connecting to WiFi... \n");
      return;
    }
  }

  IPAddress ip = WiFi.localIP();

  Serial.printf("WiFi Connected - IP Address: %u.%u.%u.%u \n", ip[0], ip[1], ip[2], ip[3]);
  updateTimeViaNTP();
  startServer();
};

void NetworkManager::updateTimeViaNTP(){
  if(WiFi.status() == WL_CONNECTED){
    configTime(GMT_OFFSET, DAY_OFFSET, NTP_SERVER_PL_0, NTP_SERVER_PL_1, NTP_SERVER_PL_2);
  }
  else{
    Logger::log("WiFi connection not available - Time update is not possible...");
  }
};

void NetworkManager::startServer(){
  if(NULL != &m_server){
    m_server.on("/humidity", HTTP_GET, [this](AsyncWebServerRequest *request){
      // HumidityData humidityData = getDataProvider()->getHumidityDataById(0);
      // String response = String(humidityData);
      // request->send(200, "text/html", response);
    });

    m_server.on("/time", HTTP_GET, [this](AsyncWebServerRequest *request){
      String timeData = getDataProvider()->getCurrentTime();
      String response = String(timeData);
      request->send(200, "text/html", response);
    });

    m_server.on("/threshold", HTTP_POST, [this](AsyncWebServerRequest * request) 
    {
      int paramsNr = request->params();
      AsyncWebParameter * param = request->getParam(0);
      int threshold = param->value().toInt();

      Serial.printf("Threshold to set: %d \n", threshold);
      // getDataProvider()->setHumidityThreshold(param->value().toInt());

      request->send(200);
  });

  m_server.begin();
  }
};