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
#include "DataProvider.hpp"
#include "Component.hpp"

class NetworkManager : public Component
{
private:
    void updateTimeViaNTP();
    void startServer();

public:
    void init() override;
    void cyclic() override;
};
#endif // NETWORK_HANDLER_HPP
