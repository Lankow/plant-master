/*
 *   ValveHandler.cpp
 *   ----------------------
 *   Created on: 2023/12/01
 *   Author: Lankow
 */
#include "handler/ValveHandler.hpp"
#include "Logger.hpp"

void ValveHandler::handleValves()
{
    uint8_t sensorToWater = getDataProvider()->getSensorToWater();

    switch (sensorToWater)
    {
    case NO_SENSOR:
        // Close Valve
        break;
    default:
        // Open Valve
        break;
    }
}

void ValveHandler::cyclic()
{
    getLogger()->log(Logger::INFO, "ValveHandler - Cyclic Task");
    handleValves();
}