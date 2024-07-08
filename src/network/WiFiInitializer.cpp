/**
 * @file WiFiInitializer.cpp
 * @date   2024-05-26
 * @author Lankow
 * @version 1.0
 *
 * @brief This file contains the implementation of the WiFiInitializer class.
 *
 * The WiFiInitializer class is responsible for managing the WiFi connection
 * for the device, including connecting to a WiFi network and handling connection status.
 */
#include "network/WiFiInitializer.hpp"
#include "config/Constants.hpp"

WiFiInitializer::WiFiInitializer() : m_preferences(), m_server(Network::Ports::ASYNC_SERVER) {}

bool WiFiInitializer::init()
{
    if (!wifiCredentialsExist())
    {
        setupAccessPoint();
        return false;
    }

    if (!connectToWiFi())
    {
        clearWifiCredentials();
        setupAccessPoint();
        return false;
    }

    IPAddress ip = WiFi.localIP();
    Serial.printf("WiFi Connected - IP Address: %u.%u.%u.%u \n", ip[0], ip[1], ip[2], ip[3]);
    return true;
}

bool WiFiInitializer::wifiCredentialsExist()
{
    if (!m_preferences.begin("wifi-config", true))
    {
        Serial.println("Failed to open NVS namespace.");
        return false;
    }
    bool ssidExists = m_preferences.isKey("ssid");
    bool passwordExists = m_preferences.isKey("password");
    m_preferences.end();
    return ssidExists && passwordExists;
}

bool WiFiInitializer::connectToWiFi()
{
    if (!m_preferences.begin("wifi-config", false))
    {
        Serial.println("Failed to open NVS namespace.");
        return false;
    }
    String ssid = m_preferences.getString("ssid");
    String password = m_preferences.getString("password");
    m_preferences.end();

    WiFi.begin(ssid.c_str(), password.c_str());

    int retryCount = 0;
    while (WiFi.status() != WL_CONNECTED && retryCount < 20)
    {
        delay(500);
        retryCount++;
    }

    return WiFi.status() == WL_CONNECTED;
}

void WiFiInitializer::clearWifiCredentials()
{
    if (!m_preferences.begin("wifi-config", false))
    {
        Serial.println("Failed to open NVS namespace.");
        return;
    }
    m_preferences.remove("ssid");
    m_preferences.remove("password");
    m_preferences.end();
}

void WiFiInitializer::setupAccessPoint()
{
    WiFi.softAP(Config::PAGE_SSID.c_str(), Config::PAGE_PASSWORD.c_str());
    m_apIP = WiFi.softAPIP();

    m_server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
                { request->send(200, "text/html", R"(
            <!DOCTYPE html>
            <html>
            <body>
                <h1>Configure WiFi</h1>
                <form action="/save" method="POST">
                    SSID: <input type="text" name="ssid"><br>
                    Password: <input type="password" name="password"><br>
                    <input type="submit" value="Save">
                </form>
            </body>
            </html>
        )"); });

    m_server.on("/save", HTTP_POST, [this](AsyncWebServerRequest *request)
                {
        String ssid, password;
        if (request->hasParam("ssid", true))
        {
            ssid = request->getParam("ssid", true)->value();
        }
        if (request->hasParam("password", true))
        {
            password = request->getParam("password", true)->value();
        }

        if (!ssid.isEmpty() && !password.isEmpty())
        {
            if (!m_preferences.begin("wifi-config", false))
            {
                Serial.println("Failed to open NVS namespace.");
                return;
            }
            m_preferences.putString("ssid", ssid);
            m_preferences.putString("password", password);
            m_preferences.end();

            request->send(200, "text/plain", "Credentials saved. Rebooting...");

            WiFi.begin(ssid.c_str(), password.c_str());
            int retryCount = 0;
            while (WiFi.status() != WL_CONNECTED && retryCount < 20)
            {
                delay(500);
                retryCount++;
            }

            if (WiFi.status() == WL_CONNECTED)
            {
                ESP.restart();
            }
            else
            {
                clearWifiCredentials();
            }
        }
        else
        {
            request->send(400, "text/plain", "Invalid input");
        } });

    m_server.begin();
    Serial.println(m_apIP.toString());
}