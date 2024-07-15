/**
 * @file ServerManager.hpp
 * @date   2024-05-27
 * @author Lankow
 * @version 1.0
 *
 * @brief This file contains the definition of the ServerManager class.
 *
 * The ServerManager class is responsible for managing the web server and WebSocket
 * connections for the device, including handling HTTP requests and WebSocket events.
 */
#ifndef SERVER_MANAGER_HPP
#define SERVER_MANAGER_HPP

#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include <memory>
#include "utilities/DisplayRenderer.hpp"
#include "utilities/JSONConverter.hpp"
#include "data/DataStorage.hpp"

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