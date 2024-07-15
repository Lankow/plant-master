/**
 * @file WiFiInitializer.hpp
 * @date   2024-05-26
 * @author Lankow
 * @version 1.0
 *
 * @brief This file contains the definition of the WiFiInitializer class.
 *
 * The WiFiInitializer class is responsible for managing the WiFi connection
 * for the device, including connecting to a WiFi network and handling connection status.
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