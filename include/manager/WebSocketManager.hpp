/*
 *   WebSocketManager.hpp
 *   ----------------------
 *   Created on: 2023/12/21
 *   Author: Lankow
 */
#ifndef WEB_SOCKET_MANAGER_HPP
#define WEB_SOCKET_MANAGER_HPP
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include "Component.hpp"
#include "constants.hpp"

class WebSocketManager : public Component
{
public:
  WebSocketManager(std::shared_ptr<AsyncWebServer> server, std::shared_ptr<AsyncWebSocket> websocket);

  void init() override;
  void cyclic() override;

private:
  void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len);
  void handleWsDataEvent(WebSocketEvtType evtType, uint8_t *data, size_t len);

  std::shared_ptr<AsyncWebSocket> m_websocket;
  std::shared_ptr<AsyncWebServer> m_server;
};
#endif // SERVER_MANAGER_HPP