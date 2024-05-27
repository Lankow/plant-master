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

class ServerManager
{
    public:
    ServerManager();
    
    void init();

    private:
    AsyncWebServer m_server;
    AsyncWebSocket m_websocket;

    void initServer();
    void initSPIFFS();
    void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len);
    void redirectToIndex(AsyncWebServerRequest *request);
};

#endif // SERVER_MANAGER_HPP