#include <Arduino.h>
#include <memory>
#include "Configurator.hpp"
#include "PlantMaster.hpp"
#include "PlantMonitor.hpp"
#include "Constants.hpp"
#include "ResetHandler.hpp"

std::shared_ptr<Configurator> configurator;
ResetHandler resetHandler;

#ifdef PLANT_MASTER
std::shared_ptr<PlantMaster> plantMaster;
#else
std::shared_ptr<PlantMonitor> plantMonitor;
#endif

void setup()
{
    Serial.begin(115200);
    resetHandler.init();

    // Initialize the configurator
    configurator = std::make_shared<Configurator>();
    configurator->init();

#ifdef PLANT_MASTER
    plantMaster = std::make_shared<PlantMaster>(configurator);
    plantMaster->init();
#else
    plantMonitor = std::make_shared<PlantMonitor>(configurator);
    plantMonitor->init();
#endif
}

void loop()
{
    resetHandler.cyclic();
#ifdef PLANT_MASTER
    plantMaster->cyclic();
#else
    plantMonitor->cyclic();
#endif
    delay(CYCLE_TIME_MS);
}