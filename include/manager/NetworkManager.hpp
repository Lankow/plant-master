/*
 *   NetworkManager.hpp
 *   ----------------------
 *   Created on: 2023/09/26
 *   Author: Lankow
 */
#ifndef NETWORK_MANAGER_HPP
#define NETWORK_MANAGER_HPP

#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "Component.hpp"
#include "ServerManager.hpp"
#include "WebSocketManager.hpp"

class NetworkManager : public Component
{
public:
    NetworkManager();

    void init() override;
    void cyclic() override;

private:
    ServerManager m_serverManager;
    WebSocketManager m_webSocketManager;

    void initWiFi();
    void initTimeViaNTP();
    void initSPIFFS();
};
#endif // NETWORK_HANDLER_HPP
