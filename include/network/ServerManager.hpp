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

/**
 * @class ServerManager
 * @brief Manages the web server and WebSocket connections for the device.
 */
class ServerManager
{
public:
    /**
     * @brief Constructs a new ServerManager object.
     * @param dataStorage A shared pointer to a DataStorage object for storing data.
     */
    ServerManager(std::shared_ptr<DataStorage> dataStorage);

    /**
     * @brief Initializes the web server and WebSocket.
     */
    void init();

    /**
     * @brief Periodically updates the WebSocket connections.
     */
    void cyclic();

private:
    AsyncWebServer m_server;       /**< Web server for handling HTTP requests. */
    AsyncWebSocket m_websocket;    /**< WebSocket for handling WebSocket connections. */
    JSONConverter m_jsonConverter; /**< JSON converter for handling data serialization and deserialization. */

    /**
     * @brief Initializes the server and sets up routes and handlers.
     */
    void initServer();

    /**
     * @brief Handles WebSocket events.
     * @param server The WebSocket server.
     * @param client The WebSocket client.
     * @param type The event type.
     * @param arg Event-specific arguments.
     * @param data The data received.
     * @param len The length of the data.
     */
    void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len);

    /**
     * @brief Redirects the client to the index page.
     * @param request The HTTP request.
     */
    void redirectToIndex(AsyncWebServerRequest *request);
};

#endif // SERVER_MANAGER_HPP