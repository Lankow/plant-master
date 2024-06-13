#include <Arduino.h>
#include <SPIFFS.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <AsyncWebSocket.h>
#include "ServerManager.hpp"
#include "Constants.hpp"

ServerManager::ServerManager(std::shared_ptr<DataStorage> dataStorage)
    : m_server(ASYNC_SERVER_PORT),
      m_websocket("/ws"),
      m_jsonConverter(dataStorage)
{
}

void ServerManager::init()
{
  if (WiFi.status() == WL_CONNECTED)
  {
    Serial.println("Initializing Server...");
    if (!initSPIFFS())
    {
      Serial.println("Failed to initialize SPIFFS");
      return;
    }
    initServer();
  }
  else
  {
    Serial.println("WiFi not connected. Server initialization aborted.");
  }
}

void ServerManager::cyclic()
{
  std::string message = m_jsonConverter.serializeDataStorage();

  m_websocket.textAll(message.c_str());
}
void ServerManager::initServer()
{
  m_websocket.onEvent([this](AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len)
                      { this->onEvent(server, client, type, arg, data, len); });

  m_server.addHandler(&m_websocket);

  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Methods", "GET, POST, PUT");
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Headers", "Content-Type");

  m_server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");
  m_server.onNotFound([this](AsyncWebServerRequest *request)
                      { this->redirectToIndex(request); });

  m_server.begin();
  Serial.printf("Server started on http://%s\n", WiFi.localIP().toString().c_str());
}

void ServerManager::redirectToIndex(AsyncWebServerRequest *request)
{
  request->redirect("http://" + WiFi.localIP().toString());
}

bool ServerManager::initSPIFFS()
{
  if (!SPIFFS.begin(true))
  {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return false;
  }
  return true;
}

void ServerManager::onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len)
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
    Serial.println("WS_EVT_DATA");
    // Handle incoming WebSocket data here
    break;
  case WS_EVT_PONG:
  case WS_EVT_ERROR:
    // Handle pong and error events if needed
    break;
  }
}
