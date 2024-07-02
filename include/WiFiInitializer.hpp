/*
 *   WiFiInitializer.hpp
 *   ----------------------
 *   Created on: 2024/05/26
 *   Author: Lankow
 */
#ifndef WIFI_INITIALIZER_HPP
#define WIFI_INITIALIZER_HPP

#include <ESPAsyncWebServer.h>
#include <Preferences.h>
#include <memory>

class WiFiInitializer
{
public:
    WiFiInitializer();

    bool init();

private:
    AsyncWebServer m_server;
    IPAddress m_apIP;
    Preferences m_preferences;

    bool wifiCredentialsExist();
    bool connectToWiFi();
    void clearWifiCredentials();
    void setupAccessPoint();
};

#endif // WIFI_INITIALIZER_HPP