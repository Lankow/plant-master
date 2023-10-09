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

class NetworkManager 
{   
    private:
    DataProvider* m_dataProvider;

    void updateTimeViaNTP();
    void startServer();

    public:
    NetworkManager(DataProvider* p_dataProvider);

    void init();
};
#endif // NETWORK_HANDLER_HPP
