#include <Arduino.h>
#include <memory> 

#include "DisplayRenderer.hpp"
#include "WiFiInitializer.hpp"
#include "ServerManager.hpp"
#include "Constants.hpp"

#ifdef PLANT_MASTER_SERVER
std::shared_ptr<DisplayRenderer> displayRenderer = std::make_shared<DisplayRenderer>();
std::shared_ptr<WiFiInitializer> wiFiInitializer = std::make_shared<WiFiInitializer>(displayRenderer, ASYNC_SERVER_PORT);
std::shared_ptr<ServerManager> serverManager = std::make_shared<ServerManager>(displayRenderer);
#endif

void setup() {
    Serial.begin(115200);
    #ifdef PLANT_MASTER_SERVER
    if (wiFiInitializer->connectToSavedWiFiOrSetupAP()) {
        Serial.println("Connected to WiFi successfully.");
        serverManager->init();
    }
    #else
    Serial.println("Plant Master Sensor.");
    #endif
}

void loop(){
    delay(1000);
}