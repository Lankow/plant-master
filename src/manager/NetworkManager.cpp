/*
*   NetworkManager.cpp
*   ----------------------
*   Created on: 2023/09/26
*   Author: Lankow
*/
#include "manager/NetworkManager.hpp"
#include "config.hpp"
#include "constants.hpp"
#include "Logger.hpp"
#include "JSONFormatter.hpp"

AsyncWebServer m_server(80);
JSONFormatter m_JSONFormatter(nullptr);

void NetworkManager::init() {
  m_JSONFormatter = JSONFormatter(getDataProvider());
  uint8_t connectionCounter = 0;

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.printf("Connecting to SSID: %s \n", WIFI_SSID);
  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);

    connectionCounter++;

    if(connectionCounter >= MAX_RETRIES){
        getLogger()->log(Logger::ERROR, "Encountered error when connecting to WiFi... \n");
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
      getLogger()->log(Logger::ERROR, "WiFi connection not available - Time update is not possible...");
  }
};

void NetworkManager::startServer(){
  if(NULL != &m_server){
    m_server.on("/humidity", HTTP_GET, [this](AsyncWebServerRequest *request){
      request->send(200, "application/json", m_JSONFormatter.serialize(JSONFormatter::HUMIDITY));
    });

    m_server.on("/temperature", HTTP_GET, [this](AsyncWebServerRequest *request){
      request->send(200, "application/json", m_JSONFormatter.serialize(JSONFormatter::TEMPERATURE));
    });

    m_server.on("/room-humidity", HTTP_GET, [this](AsyncWebServerRequest *request){
      request->send(200, "application/json", m_JSONFormatter.serialize(JSONFormatter::ROOM_HUMIDITY));
    });

    m_server.on("/sensor", HTTP_GET, [this](AsyncWebServerRequest *request){
      request->send(200, "application/json", m_JSONFormatter.serialize(JSONFormatter::SENSOR));
    });

    m_server.on("/time", HTTP_GET, [this](AsyncWebServerRequest *request){
      request->send(200, "application/json", m_JSONFormatter.serialize(JSONFormatter::TIME));
    });

    m_server.on("/humidity", HTTP_POST, [this](AsyncWebServerRequest * request) 
    {
      if (request->args() == 0) // no arguments attached -> STATUS_BAD_REQUEST
        return request->send(400, "application/json", F("ERROR: Bad or no arguments"));

      uint8_t handlerId = request->arg("id").toInt();    
      uint16_t newThreshold = request->arg("threshold").toInt();

      getDataProvider()->setHumidityThreshold(handlerId, newThreshold);

      request->send(200, "text/html", "Threshold updated successfully.");
    });

  m_server.begin();
  }
};