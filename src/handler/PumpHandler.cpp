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
    uint8_t sensorToWater = m_dataProvider->getSensorToWater();

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

void PumpHandler::init()
{
    m_logger->log(Logger::INFO, "PumpHandler - Init");
}

void PumpHandler::cyclic()
{
    m_logger->log(Logger::INFO, "PumpHandler - Cyclic Task");
    handlePump();
}