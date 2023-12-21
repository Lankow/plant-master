/*
 *   NetworkManager.cpp
 *   ----------------------
 *   Created on: 2023/09/26
 *   Author: Lankow
 */
#include <SPIFFS.h>
#include "manager/NetworkManager.hpp"
#include "config.hpp"
#include "constants.hpp"
#include "utils/Logger.hpp"
#include "utils/JSONUtil.hpp"
#include "utils/SDCardUtil.hpp"

std::shared_ptr<AsyncWebServer> m_server = std::make_shared<AsyncWebServer>(80);
std::shared_ptr<AsyncWebSocket> m_websocket = std::make_shared<AsyncWebSocket>("/ws");

NetworkManager::NetworkManager() : m_serverManager(m_server), m_webSocketManager(m_server, m_websocket){};

void NetworkManager::init()
{
  initWiFi();
  initTimeViaNTP();
  initSPIFFS();
  m_webSocketManager.init();
  m_webSocketManager.setDataProvider(m_dataProvider);
  m_serverManager.init();
};

void NetworkManager::cyclic()
{
  Logger::log(Logger::INFO, "NetworkManager - Cyclic Task");
  m_webSocketManager.cyclic();
};

void NetworkManager::initTimeViaNTP()
{
  if (WiFi.status() == WL_CONNECTED)
  {
    configTime(GMT_OFFSET, DAY_OFFSET, NTP_SERVER_PL_0.c_str(), NTP_SERVER_PL_1.c_str(), NTP_SERVER_PL_2.c_str());
  }
  else
  {
    Logger::log(Logger::ERROR, "WiFi connection not available - Time update is not possible...");
  }
};

void NetworkManager::initSPIFFS()
{
  if (!SPIFFS.begin(true))
  {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }
};

void NetworkManager::initWiFi()
{
  uint8_t connectionCounter = 0;

  if (!WiFi.config(LOCAL_IP, GATEWAY, SUBNET, PRIMARY_DNS, SECONDARY_DNS))
  {
    Serial.println("STA Failed to configure");
    return;
  }

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.printf("Connecting to SSID: %s \n", WIFI_SSID);

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print('.');
    delay(1000);

    connectionCounter++;

    if (connectionCounter >= MAX_RETRIES)
    {
      Logger::log(Logger::ERROR, "Encountered error when connecting to WiFi... \n");
      return;
    }
  }

  IPAddress ip = WiFi.localIP();

  Serial.printf("WiFi Connected - IP Address: %u.%u.%u.%u \n", ip[0], ip[1], ip[2], ip[3]);
}
