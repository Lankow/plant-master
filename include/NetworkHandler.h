/*
*   NetworkHandler.h
*   ----------------------
*   Created on: 2023/09/26
*   Author: Lankow
*/
#include <WiFi.h>

class NetworkHandler
{   
    public:
    NetworkHandler();

    void initWiFi();
    void updateTimeViaNTP();
};





