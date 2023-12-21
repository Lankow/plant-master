/*
 *   ServerManager.cpp
 *   ----------------------
 *   Created on: 2023/12/21
 *   Author: Lankow
 */
#include <SPIFFS.h>
#include "manager/ServerManager.hpp"

ServerManager::ServerManager(std::shared_ptr<AsyncWebServer> server) : m_server(server){};

void ServerManager::init()
{
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Methods", "GET, POST, PUT");
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Headers", "Content-Type");

  m_server->serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");
  m_server->onNotFound([this](AsyncWebServerRequest *request)
                       { this->redirectToIndex(request); });
  m_server->begin();
}

void ServerManager::cyclic()
{
}

void ServerManager::redirectToIndex(AsyncWebServerRequest *request)
{
  request->redirect("http://" + WiFi.localIP().toString());
}