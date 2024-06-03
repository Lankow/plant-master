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
#include "DisplayRenderer.hpp"

class WiFiInitializer
{
public:
    WiFiInitializer(std::shared_ptr<DisplayRenderer> displayRenderer, uint16_t port);

    bool init();

private:
    std::shared_ptr<DisplayRenderer> m_displayRenderer;
    AsyncWebServer m_server;
    IPAddress m_apIP;
    Preferences m_preferences;

    bool wifiCredentialsExist();
    bool connectMonitorRequested();
    bool connectToWiFi();
    void clearWifiCredentials();
    void setupAccessPoint();
};

#endif // WIFI_INITIALIZER_HPP