#include <Arduino.h>
#include <memory> 

#include "DisplayRenderer.hpp"
#include "WiFiInitializer.hpp"
#include "ServerManager.hpp"
#include "HumidityReader.hpp"
#include "DHTReader.hpp"
#include "WaterPumpController.hpp"
#include "ValveController.hpp"
#include "Constants.hpp"

#ifdef PLANT_MASTER_SERVER
std::shared_ptr<DisplayRenderer> displayRenderer = std::make_shared<DisplayRenderer>();
std::shared_ptr<WiFiInitializer> wiFiInitializer = std::make_shared<WiFiInitializer>(displayRenderer, ASYNC_SERVER_PORT);
std::shared_ptr<ServerManager> serverManager = std::make_shared<ServerManager>(displayRenderer);
#else
std::shared_ptr<HumidityReader> humidityReader = std::make_shared<HumidityReader>(EspPins::PIN_34);
std::shared_ptr<DHTReader> dhtReader = std::make_shared<DHTReader>(EspPins::PIN_21);
std::shared_ptr<WaterPumpController> waterPumpController = std::make_shared<WaterPumpController>(EspPins::PIN_17);
std::shared_ptr<ValveController> valveController = std::make_shared<ValveController>(EspPins::PIN_18);
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
    #ifdef PLANT_MASTER_SERVER
    serverManager->cyclic();
    #else
    humidityReader->readHumidity();
    dhtReader->readRoomHumidity();
    dhtReader->readRoomTemperature();
    waterPumpController->toggle();
    valveController->toggle();
    #endif
    delay(1000);
}