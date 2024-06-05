#include <Arduino.h>
#include <memory>
#include "PlantMaster.hpp"
#include "PlantMonitor.hpp"
#include "Constants.hpp"

#define PLANT_MASTER

#ifdef PLANT_MASTER
PlantMaster plantMaster;
#else
PlantMonitor plantMonitor;
#endif

void setup()
{
    Serial.begin(115200);
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