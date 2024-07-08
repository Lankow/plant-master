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

/**
 * @class WiFiInitializer
 * @brief A class for initializing and managing WiFi connections.
 *
 * The WiFiInitializer class handles connecting to WiFi networks, checking for existing credentials,
 * clearing credentials, and setting up an access point for configuration.
 */
class WiFiInitializer
{
public:
    /**
     * @brief Constructs a new WiFiInitializer object.
     */
    WiFiInitializer();

    /**
     * @brief Initializes the WiFi connection.
     *
     * This method checks for existing WiFi credentials and attempts to connect to the WiFi network.
     * If no credentials are found or the connection fails, it sets up an access point.
     *
     * @return true if WiFi is connected successfully, false otherwise.
     */
    bool init();

private:
    AsyncWebServer m_server;   /**< Web server instance. */
    IPAddress m_apIP;          /**< Access point IP address. */
    Preferences m_preferences; /**< Preferences for storing WiFi credentials. */

    /**
     * @brief Checks if WiFi credentials exist in the preferences.
     *
     * @return true if WiFi credentials exist, false otherwise.
     */
    bool wifiCredentialsExist();

    /**
     * @brief Attempts to connect to the WiFi network.
     *
     * @return true if connected successfully, false otherwise.
     */
    bool connectToWiFi();

    /**
     * @brief Clears the stored WiFi credentials.
     */
    void clearWifiCredentials();

    /**
     * @brief Sets up the device as a WiFi access point.
     */
    void setupAccessPoint();
};

#endif // WIFI_INITIALIZER_HPP