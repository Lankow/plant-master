#include <Arduino.h>
#include <Wire.h>  
#include "SSD1306Wire.h"
#include "OLEDDisplayUi.h"
#include <Preferences.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>

#define INITIAL_SCREEN_DURATION 3000
#define CONFIG_PAGE_SSID "config_plant_master"
#define CONFIG_PAGE_PASSWORD "plantmaster"

SSD1306Wire display(0x3c, SDA, SCL); 
Preferences preferences;
AsyncWebServer server(80);

void drawInitialScreen(){
    display.clear();
    display.drawString(30, 10, "Plant-Master");
    display.drawHorizontalLine(10, 26, 100);
    display.drawString(35, 30, "by Lankow");
    display.display();
}

void drawConfigScreen(){
    display.clear();
    display.drawString(10, 0, "Config SSID:");
    display.drawString(10, 10, CONFIG_PAGE_SSID);
    display.drawHorizontalLine(10, 24, 100);
    display.drawString(10, 25, "Config PASSWORD:");
    display.drawString(10, 35, CONFIG_PAGE_PASSWORD);
    display.display();
}

bool wifiCredentialsExist() {
    if (!preferences.begin("wifi-config", true)) {
        Serial.println("Failed to open NVS namespace.");
        return false;
    }
    bool ssidExists = preferences.isKey("ssid");
    bool passwordExists = preferences.isKey("password");
    preferences.end();
    return ssidExists && passwordExists;
}

bool connectToWiFi() {
    if (!preferences.begin("wifi-config", false)) {
        Serial.println("Failed to open NVS namespace.");
        return false;
    }
    String ssid = preferences.getString("ssid");
    String password = preferences.getString("password");
    preferences.end();

    WiFi.begin(ssid.c_str(), password.c_str());

    int retryCount = 0;
    while (WiFi.status() != WL_CONNECTED && retryCount < 20) {
        delay(500);
        retryCount++;
    }

    return WiFi.status() == WL_CONNECTED;
}

void clearWifiCredentials() {
    if (!preferences.begin("wifi-config", false)) {
        Serial.println("Failed to open NVS namespace.");
        return;
    }
    preferences.remove("ssid");
    preferences.remove("password");
    preferences.end();
}

void setupAccessPoint() {
    WiFi.softAP(CONFIG_PAGE_SSID, CONFIG_PAGE_PASSWORD);

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(200, "text/html", R"(
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
        )");
    });

    server.on("/save", HTTP_POST, [](AsyncWebServerRequest *request) {
        String ssid, password;
        if (request->hasParam("ssid", true)) {
            ssid = request->getParam("ssid", true)->value();
        }
        if (request->hasParam("password", true)) {
            password = request->getParam("password", true)->value();
        }

        if (!ssid.isEmpty() && !password.isEmpty()) {
            if (!preferences.begin("wifi-config", false)) {
                Serial.println("Failed to open NVS namespace.");
                return;
            }
            preferences.putString("ssid", ssid);
            preferences.putString("password", password);
            preferences.end();

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
        }
    });

    server.begin();
}

bool connectToSavedWiFiOrSetupAP() {
    if (wifiCredentialsExist()) {
        if (connectToWiFi()) {
            return true;
        } else {
            clearWifiCredentials();
        }
    }
    setupAccessPoint();
    drawConfigScreen();
    return false;
}
void setup() {
    Serial.begin(115200);

    display.init();
    drawInitialScreen();
    delay(INITIAL_SCREEN_DURATION);

    if (connectToSavedWiFiOrSetupAP()) {
        Serial.println("Connected to WiFi successfully.");
    } else {
        Serial.println("Failed to connect to WiFi. Access Point 'config_plant_master' is set up.");
    }
}

void loop() {
    delay(1000);
}