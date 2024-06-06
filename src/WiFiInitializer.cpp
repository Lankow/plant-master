/*
 *   WiFiInitializer.cpp
 *   ----------------------
 *   Created on: 2024/05/26
 *   Author: Lankow
 */
#include <WiFi.h>
#include "WiFiInitializer.hpp"
#include "Constants.hpp"

WiFiInitializer::WiFiInitializer() : m_preferences(), m_server(ASYNC_SERVER_PORT){};

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

#ifdef PLANT_MASTER
    if (!WiFi.config(LOCAL_IP, GATEWAY, SUBNET, PRIMARY_DNS, SECONDARY_DNS))
    {
        Serial.println("STA Failed to configure");
        return false;
    }
#endif

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
    WiFi.softAP(CONFIG_PAGE_SSID.c_str(), CONFIG_PAGE_PASSWORD.c_str());
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
        if (request->hasParam("ssid", true)) {
            ssid = request->getParam("ssid", true)->value();
        }
        if (request->hasParam("password", true)) {
            password = request->getParam("password", true)->value();
        }

        if (!ssid.isEmpty() && !password.isEmpty()) {
            if (!m_preferences.begin("wifi-config", false)) {
                Serial.println("Failed to open NVS namespace.");
                return;
            }
            m_preferences.putString("ssid", ssid);
            m_preferences.putString("password", password);
            m_preferences.end();

            request->send(200, "text/plain", "Credentials saved. Rebooting...");

            // Attempt to connect to WiFi
            WiFi.begin(ssid.c_str(), password.c_str());
            int retryCount = 0;
            while (WiFi.status() != WL_CONNECTED && retryCount < 20) {
                delay(500);
                retryCount++;
            }

            if (WiFi.status() == WL_CONNECTED) {
                ESP.restart(); // Restart to apply changes
            } else {
                clearWifiCredentials(); // Clear invalid credentials
            }
        } else {
            request->send(400, "text/plain", "Invalid input");
        } });

    m_server.begin();
    Serial.println(m_apIP.toString());
}
