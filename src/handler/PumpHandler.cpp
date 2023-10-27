/*
 *   PumpHandler.cpp
 *   ----------------------
 *   Created on: 2023/10/10
 *   Author: Lankow
 */
#include "handler/PumpHandler.hpp"
#include "Logger.hpp"

void PumpHandler::handlePump()
{
    uint8_t sensorToWater = getDataProvider()->getSensorToWater();

    switch (sensorToWater)
    {
    case NO_SENSOR:
        // Turn off Pump
        break;
    default:
        // Launch Pump
        break;
    }
}

void PumpHandler::cyclic()
{
    getLogger()->log(Logger::INFO, "PumpHandler - Cyclic Task");
    handlePump();
}