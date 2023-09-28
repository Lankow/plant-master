/*
*   NetworkHandler.h
*   ----------------------
*   Created on: 2023/09/26
*   Author: Lankow
*/
#include <WiFi.h>

class NetworkHandler
{   
    private:
    WiFiServer m_server;
    WiFiClient m_client;

    void updateTimeViaNTP();
    void startServer();

    public:
    NetworkHandler();

    void initWiFi();
    void handleClient();
    void html();
};





