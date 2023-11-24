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
#include "SPIFFS.h"

AsyncWebServer m_server(80);
AsyncWebSocket m_websocket("/ws");
JSONFormatter m_JSONFormatter(nullptr);

void NetworkManager::init()
{
  m_JSONFormatter = JSONFormatter(m_dataProvider);
  initWiFi();
  initTimeViaNTP();
  initSPIFFS();
  initWebSocket();
  initServer();
};

void NetworkManager::cyclic()
{
  m_logger->log(Logger::INFO, "NetworkManager - Cyclic Task");
  std::string message = m_JSONFormatter.serialize(JSONFormatter::HUMIDITY);
  m_websocket.textAll(message.c_str());
};

void redirectToIndex(AsyncWebServerRequest *request)
{
  request->redirect("http://" + WiFi.localIP().toString());
}

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len)
{
  switch (type)
  {
  case WS_EVT_CONNECT:
    Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
    break;
  case WS_EVT_DISCONNECT:
    Serial.printf("WebSocket client #%u disconnected\n", client->id());
    break;
  case WS_EVT_DATA:
  case WS_EVT_PONG:
  case WS_EVT_ERROR:
    break;
  }
}

void NetworkManager::initTimeViaNTP()
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
      m_logger->log(Logger::ERROR, "Encountered error when connecting to WiFi... \n");
      return;
    }
  }

  IPAddress ip = WiFi.localIP();

  Serial.printf("WiFi Connected - IP Address: %u.%u.%u.%u \n", ip[0], ip[1], ip[2], ip[3]);
}

void NetworkManager::initWebSocket()
{
  m_websocket.onEvent(onEvent);
  m_server.addHandler(&m_websocket);
}

void NetworkManager::initServer()
{
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Methods", "GET, POST, PUT");
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Headers", "Content-Type");

  m_server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");
  m_server.onNotFound(redirectToIndex);
  m_server.begin();
};
