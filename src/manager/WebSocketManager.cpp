/*
 *   WebSocketManager.cpp
 *   ----------------------
 *   Created on: 2023/12/21
 *   Author: Lankow
 */
#include "manager/WebSocketManager.hpp"
#include "utils/JSONUtil.hpp"
#include "utils/SDCardUtil.hpp"
#include "utils/Logger.hpp"

WebSocketManager::WebSocketManager(std::shared_ptr<AsyncWebServer> server,
                                   std::shared_ptr<AsyncWebSocket> websocket) : m_server(server), m_websocket(websocket){};

void WebSocketManager::init()
{
  m_websocket->onEvent([this](AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len)
                       { this->onEvent(server, client, type, arg, data, len); });
  m_server->addHandler(m_websocket.get());
}

void WebSocketManager::cyclic()
{
  std::string message = JSONUtil::serialize(m_dataProvider);
  m_websocket->textAll(message.c_str());
}

void WebSocketManager::onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len)
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
    Serial.println("Entered here");
    break;
  case WS_EVT_PONG:
  case WS_EVT_ERROR:
    break;
  }
}

void WebSocketManager::handleWsDataEvent(WebSocketEvtType evtType, uint8_t *data, size_t len)
{
  uint16_t threshold;
  uint8_t id;
  std::vector<std::string> logsList;
  std::string logsJson;

  switch (evtType)
  {
  case WebSocketEvtType::SET_THRESHOLD:
    threshold = JSONUtil::deserializeByKey(data, len, "threshold");
    id = JSONUtil::deserializeByKey(data, len, "id");
    m_dataProvider->setHandlerThreshold(id, threshold);
    break;
  case WebSocketEvtType::GET_LOGS:
    logsList = SDCardUtil::getListOfLogFiles();
    logsJson = JSONUtil::toJSONString(logsList);
    m_websocket->textAll(logsJson.c_str());
    break;
  case WebSocketEvtType::UNKNOWN:
  default:
    Logger::log(Logger::ERROR, "Unknown Type of WS Data Event to be handled.");
  }
}
