#include <Arduino.h>
#include <memory>
#include "PlantMaster.hpp"
#include "PlantMonitor.hpp"
#include "Constants.hpp"
#include "ConfigHandler.hpp"
#include "ResetHandler.hpp"

std::shared_ptr<ConfigHandler> configHandler;
ResetHandler resetHandler;

#ifdef PLANT_MASTER
PlantMaster plantMaster(configHandler);
#else
PlantMonitor plantMonitor(configHandler);
#endif

void setup()
{
    Serial.begin(115200);
    resetHandler.init();
    configHandler->init();

#ifdef PLANT_MASTER
    plantMaster.init();
#else
    plantMonitor.init();
#endif
}

void loop()
{
    resetHandler.cyclic();
#ifdef PLANT_MASTER
    plantMaster.cyclic();
#else
    plantMonitor.cyclic();
#endif
    delay(CYCLE_TIME_MS);
}