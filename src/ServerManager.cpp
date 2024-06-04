/*
 *   ServerManager.cpp
 *   ----------------------
 *   Created on: 2024/05/27
 *   Author: Lankow
 */
#include <Arduino.h>
#include <SPIFFS.h>
#include <WiFi.h>
#include <Preferences.h>
#include "ServerManager.hpp"
#include "Constants.hpp"

ServerManager::ServerManager() : m_server(ASYNC_SERVER_PORT), m_websocket(WEBSOCKET_URL.c_str()){};

void ServerManager::init()
{
  if (WiFi.status() == WL_CONNECTED)
  {
    Serial.println("Initializing Server...");
    initSPIFFS();
    initServer();
  }
}

void ServerManager::cyclic()
{
  m_websocket.textAll("");
}

void ServerManager::performReset()
{
  Preferences preferences;

  if (!preferences.begin("wifi-config", false))
  {
    Serial.println("Failed to open NVS namespace.");
    return;
  }

  Serial.println("Performing Plant-Master reset...");
  preferences.clear();
  preferences.end();

  delay(100);
  ESP.restart();
}

void ServerManager::initServer()
{
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Methods", "GET, POST, PUT");
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Headers", "Content-Type");

  m_websocket.onEvent([this](AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len)
                      { this->onEvent(server, client, type, arg, data, len); });
  m_server.addHandler(&m_websocket);

  m_server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");
  m_server.on("/reset", HTTP_GET, [this](AsyncWebServerRequest *request)
              {
                request->send(200, "text/plain", "Initializing Plant-Master reset...");
                this->performReset(); });

  m_server.onNotFound([this](AsyncWebServerRequest *request)
                      {
                        Serial.println("Page not found.");
                        this->redirectToIndex(request); });
  m_server.begin();
  // m_displayRenderer->drawConnectedScreen(WiFi.localIP().toString().c_str());
};

void ServerManager::redirectToIndex(AsyncWebServerRequest *request)
{
  request->redirect("http://" + WiFi.localIP().toString());
}

void ServerManager::initSPIFFS()
{
  if (!SPIFFS.begin(true))
  {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }
};

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
    break;
  case WS_EVT_PONG:
  case WS_EVT_ERROR:
    break;
  }
}
