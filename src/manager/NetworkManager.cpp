/*
 *   NetworkManager.cpp
 *   ----------------------
 *   Created on: 2023/09/26
 *   Author: Lankow
 */
#include "manager/NetworkManager.hpp"
#include "SPIFFS.h"
#include "config.hpp"
#include "constants.hpp"
#include "utils/Logger.hpp"
#include "utils/JSONUtil.hpp"
#include "utils/SDCardUtil.hpp"

AsyncWebServer m_server(80);
AsyncWebSocket m_websocket("/ws");

void NetworkManager::init()
{
  initWiFi();
  initTimeViaNTP();
  initSPIFFS();
  initWebSocket();
  initServer();
};

void NetworkManager::cyclic()
{
  Logger::log(Logger::INFO, "NetworkManager - Cyclic Task");
  std::string message = JSONUtil::serialize(m_dataProvider);
  m_websocket.textAll(message.c_str());
};

void redirectToIndex(AsyncWebServerRequest *request)
{
  request->redirect("http://" + WiFi.localIP().toString());
}

void NetworkManager::handleWsDataEvent(WebSocketEvtType evtType, uint8_t *data, size_t len)
{
  std::vector<std::string> logsList;
  std::string logsJson;
  uint16_t threshold;
  uint8_t id;

  switch (evtType)
  {
  case WebSocketEvtType::SET_THRESHOLD:
    threshold = JSONUtil::deserializeByKey(data, len, "threshold");
    id = JSONUtil::deserializeByKey(data, len, "id");

    Serial.println(threshold);
    Serial.println(id);

    m_dataProvider->setHandlerThreshold(id, threshold);
    break;
  case WebSocketEvtType::GET_LOGS:
    logsList = SDCardUtil::getListOfLogFiles();
    logsJson = JSONUtil::toJSONString(logsList);

    m_websocket.textAll(logsJson.c_str());
    break;
  case WebSocketEvtType::UNKNOWN:
  default:
    Logger::log(Logger::ERROR, "Unknown Type of WS Data Event to be handled.");
  }
}

void NetworkManager::onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len)
{
  WebSocketEvtType eventType = WebSocketEvtType::UNKNOWN;

  switch (type)
  {
  case WS_EVT_CONNECT:
    Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
    break;
  case WS_EVT_DISCONNECT:
    Serial.printf("WebSocket client #%u disconnected\n", client->id());
    break;
  case WS_EVT_DATA:
    eventType = JSONUtil::getEventType(data, len);
    handleWsDataEvent(eventType, data, len);
    break;
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

void NetworkManager::initWebSocket()
{
  m_websocket.onEvent([](AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len)
                      { static_cast<NetworkManager *>(arg)->onEvent(server, client, type, arg, data, len); });
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
