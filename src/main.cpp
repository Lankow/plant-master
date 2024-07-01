#include <Arduino.h>
#include <memory>
#include "Configurator.hpp"
#include "PlantMaster.hpp"
#include "Constants.hpp"

std::shared_ptr<Configurator> configurator;
std::shared_ptr<PlantMaster> plantMaster;

void initializeSystem()
{
    Serial.begin(115200);

    // Initialize the configurator
    configurator = std::make_shared<Configurator>();
    if (!configurator->init())
    {
        Serial.println("Failed to initialize Configurator");
        return;
    }

    // Initialize the PlantMaster
    plantMaster = std::make_shared<PlantMaster>(configurator);
    if (!plantMaster->init())
    {
        Serial.println("Failed to initialize PlantMaster");
        return;
    }

    Serial.println("System initialized successfully");
}

void setup()
{
    initializeSystem();
}

void loop()
{
    if (plantMaster)
    {
        plantMaster->cyclic();
    }
    delay(Config::CYCLE_TIME_MS);
}
