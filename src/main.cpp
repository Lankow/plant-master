#include <Arduino.h>
#include <memory> 

#include "DisplayRenderer.hpp"
#include "WiFiInitializer.hpp"
#include "Constants.hpp"

std::shared_ptr<DisplayRenderer> displayRenderer = std::make_shared<DisplayRenderer>();
std::shared_ptr<WiFiInitializer> wiFiInitializer = std::make_shared<WiFiInitializer>(displayRenderer, ASYNC_SERVER_PORT);

void setup() {
    Serial.begin(115200);
    if (wiFiInitializer->connectToSavedWiFiOrSetupAP()) {
        Serial.println("Connected to WiFi successfully.");
    } else {
        Serial.println("Failed to connect to WiFi. Access Point 'config_plant_master' is set up.");
    }
}

void loop() {
    delay(1000);
}