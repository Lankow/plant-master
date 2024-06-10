#include <Arduino.h>
#include <memory>
#include "PlantMaster.hpp"
#include "PlantMonitor.hpp"
#include "Constants.hpp"
#include "ConfigHandler.hpp"

std::shared_ptr<ConfigHandler> configHandler;

#ifdef PLANT_MASTER
PlantMaster plantMaster(configHandler);
#else
PlantMonitor plantMonitor(configHandler);
#endif

void setup()
{
    Serial.begin(115200);
    configHandler->init();
#ifdef PLANT_MASTER
    plantMaster.init();
#else
    plantMonitor.init();
#endif
}

void loop()
{
#ifdef PLANT_MASTER
    plantMaster.cyclic();
#else
    plantMonitor.cyclic();
#endif
    delay(CYCLE_TIME_MS);
}