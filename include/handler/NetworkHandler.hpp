/*
*   NetworkHandler.hpp
*   ----------------------
*   Created on: 2023/09/26
*   Author: Lankow
*/
#ifndef NETWORK_HANDLER_HPP
#define NETWORK_HANDLER_HPP

#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "Handler.hpp"

class NetworkHandler : public Handler 
{   
    private:

    void updateTimeViaNTP();
    void startServer();

    public:
    NetworkHandler();

    void initWiFi();
};
#endif // NETWORK_HANDLER_HPP
