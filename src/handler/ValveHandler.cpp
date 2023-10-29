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
    uint8_t sensorToWater = m_dataProvider->getSensorToWater();

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

void ValveHandler::init()
{
    m_logger->log(Logger::INFO, "ValveHandler - Init");
}

void ValveHandler::cyclic()
{
    m_logger->log(Logger::INFO, "ValveHandler - Cyclic Task");
    handleValves();
}