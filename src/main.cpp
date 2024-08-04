#include <Arduino.h>
#include <memory>
#include "config/Configurator.hpp"
#include "config/Constants.hpp"
#include "PlantMaster.hpp"

std::shared_ptr<Configurator> configurator;
std::shared_ptr<PlantMaster> plantMaster;

bool initializeSystem()
{
    Serial.begin(115200);

    // Configurator Initialization
    configurator = std::make_shared<Configurator>();
    if (!configurator->init())
    {
        Serial.println("Failed to initialize Configurator.");
        return false;
    }

    // PlantMaster Initialization
    plantMaster = std::make_shared<PlantMaster>(configurator);
    if (!plantMaster->init())
    {
        Serial.println("Failed to initialize PlantMaster.");
        return false;
    }

    return true;
}

void setup()
{
    if (initializeSystem())
    {
        Serial.println("Plant-Master System initialized successfully.");
    }
    else
    {
        Serial.println("Plant-Master System initialization failed. Reseting device.");
        ESP.restart();
    };
}

void loop()
{
    if (plantMaster)
    {
        plantMaster->cyclic();
    }
    delay(Config::CYCLE_TIME_MS);
}
