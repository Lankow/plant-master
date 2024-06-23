#include <Arduino.h>
#include <memory>
#include "Configurator.hpp"
#include "PlantMaster.hpp"
#include "Constants.hpp"

std::shared_ptr<Configurator> configurator;
std::shared_ptr<PlantMaster> plantMaster;

void setup()
{
    Serial.begin(115200);

    // Initialize the configurator
    configurator = std::make_shared<Configurator>();
    configurator->init();

    plantMaster = std::make_shared<PlantMaster>(configurator);
    plantMaster->init();
}

void loop()
{
    plantMaster->cyclic();
    delay(CYCLE_TIME_MS);
}