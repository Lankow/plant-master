#include <Arduino.h>
#include <memory> 

#include "DisplayRenderer.hpp"
#include "WiFiInitializer.hpp"
#include "ServerManager.hpp"
#include "PlantHumidityReader.hpp"
#include "DHTReader.hpp"
#include "WaterPumpController.hpp"
#include "ValveController.hpp"
#include "DataStorage.hpp"
#include "Constants.hpp"

#ifdef PLANT_MASTER_SERVER
std::shared_ptr<DisplayRenderer> displayRenderer = std::make_shared<DisplayRenderer>();
std::shared_ptr<WiFiInitializer> wiFiInitializer = std::make_shared<WiFiInitializer>(displayRenderer, ASYNC_SERVER_PORT);
std::shared_ptr<ServerManager> serverManager = std::make_shared<ServerManager>(displayRenderer);
std::shared_ptr<DataStorage> dataStorage = std::make_shared<DataStorage>();
#else
std::shared_ptr<PlantHumidityReader> plantHumidityReader = std::make_shared<PlantHumidityReader>(EspPins::PIN_34);
std::shared_ptr<DHTReader> dhtReader = std::make_shared<DHTReader>(EspPins::PIN_21);
std::shared_ptr<WaterPumpController> waterPumpController = std::make_shared<WaterPumpController>(EspPins::PIN_18);
std::shared_ptr<ValveController> valveController = std::make_shared<ValveController>(EspPins::PIN_12);
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
    pinMode(EspPins::PIN_18, OUTPUT);  
    #endif
}

void loop(){
    #ifdef PLANT_MASTER_SERVER
    serverManager->cyclic();
    #else
    plantHumidityReader->readHumidity();
    dhtReader->readRoomHumidity();
    dhtReader->readRoomTemperature();
    waterPumpController->turnOn();
    delay(4000);
    waterPumpController->turnOff();
    valveController->toggle();
    #endif
    delay(4000);
}