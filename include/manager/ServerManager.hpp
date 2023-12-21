/*
 *   ServerManager.hpp
 *   ----------------------
 *   Created on: 2023/12/21
 *   Author: Lankow
 */
#ifndef SERVER_MANAGER_HPP
#define SERVER_MANAGER_HPP
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <memory>
#include "Component.hpp"
#include "constants.hpp"

class ServerManager : public Component
{
public:
  ServerManager(std::shared_ptr<AsyncWebServer> server);

  void init() override;
  void cyclic() override;

private:
  std::shared_ptr<AsyncWebServer> m_server;

  void initServer();
  void redirectToIndex(AsyncWebServerRequest *request);
};

#endif // SERVER_MANAGER_HPP