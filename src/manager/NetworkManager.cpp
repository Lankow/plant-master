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

void NetworkManager::init()
{
  m_JSONFormatter = JSONFormatter(m_dataProvider);
  uint8_t connectionCounter = 0;

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.printf("Connecting to SSID: %s \n", WIFI_SSID);

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print('.');
    delay(1000);

    connectionCounter++;

    if (connectionCounter >= MAX_RETRIES)
    {
      m_logger->log(Logger::ERROR, "Encountered error when connecting to WiFi... \n");
      return;
    }
  }

  IPAddress ip = WiFi.localIP();

  Serial.printf("WiFi Connected - IP Address: %u.%u.%u.%u \n", ip[0], ip[1], ip[2], ip[3]);
  updateTimeViaNTP();
  startServer();
};

void NetworkManager::cyclic()
{
  m_logger->log(Logger::INFO, "NetworkManager - Cyclic Task");
};

void NetworkManager::updateTimeViaNTP()
{
  if (WiFi.status() == WL_CONNECTED)
  {
    configTime(GMT_OFFSET, DAY_OFFSET, NTP_SERVER_PL_0.c_str(), NTP_SERVER_PL_1.c_str(), NTP_SERVER_PL_2.c_str());
  }
  else
  {
    m_logger->log(Logger::ERROR, "WiFi connection not available - Time update is not possible...");
  }
};

void NetworkManager::startServer()
{
  m_server.on("/humidity", HTTP_GET, [this](AsyncWebServerRequest *request)
              { request->send(200, "application/json", m_JSONFormatter.serialize(JSONFormatter::HUMIDITY).c_str()); });

  m_server.on("/temperature", HTTP_GET, [this](AsyncWebServerRequest *request)
              { request->send(200, "application/json", m_JSONFormatter.serialize(JSONFormatter::TEMPERATURE).c_str()); });

  m_server.on("/room-humidity", HTTP_GET, [this](AsyncWebServerRequest *request)
              { request->send(200, "application/json", m_JSONFormatter.serialize(JSONFormatter::ROOM_HUMIDITY).c_str()); });

  m_server.on("/sensor", HTTP_GET, [this](AsyncWebServerRequest *request)
              { request->send(200, "application/json", m_JSONFormatter.serialize(JSONFormatter::SENSOR).c_str()); });

  m_server.on("/time", HTTP_GET, [this](AsyncWebServerRequest *request)
              { request->send(200, "application/json", m_JSONFormatter.serialize(JSONFormatter::TIME).c_str()); });

  m_server.on("/humidity", HTTP_POST, [this](AsyncWebServerRequest *request)
              {
      if (request->args() == 0) // no arguments attached -> STATUS_BAD_REQUEST
        return request->send(400, "application/json", F("ERROR: Bad or no arguments"));

      uint8_t handlerId = request->arg("id").toInt();    
      uint16_t newThreshold = request->arg("threshold").toInt();

      m_dataProvider->setHandlerThreshold(handlerId, newThreshold);

      request->send(200, "text/html", "Threshold updated successfully."); });

  m_server.begin();
};