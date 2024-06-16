/*
 *   ServerManager.hpp
 *   ----------------------
 *   Created on: 2024/05/27
 *   Author: Lankow
 */
#ifndef SERVER_MANAGER_HPP
#define SERVER_MANAGER_HPP

#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include <memory>
#include "DisplayRenderer.hpp"
#include "JSONConverter.hpp"

class ServerManager
{
public:
    ServerManager(std::shared_ptr<DataStorage> dataStorage);

    void init();
    void cyclic();

private:
    AsyncWebServer m_server;
    AsyncWebSocket m_websocket;
    JSONConverter m_jsonConverter;

    void initServer();
    void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len);
    void redirectToIndex(AsyncWebServerRequest *request);
};

#endif // SERVER_MANAGER_HPP