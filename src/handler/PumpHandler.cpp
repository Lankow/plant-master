/*
 *   PumpHandler.cpp
 *   ----------------------
 *   Created on: 2023/10/10
 *   Author: Lankow
 */
#include "handler/PumpHandler.hpp"
#include "utils/Logger.hpp"
#include "constants.hpp"

PumpHandler::PumpHandler(const uint8_t pin) : m_operatedPin(pin){};

void PumpHandler::handlePump()
{
    uint8_t sensorToWater = m_dataProvider->getSensorToWater();

    if (sensorToWater != NO_SENSOR)
    {
        digitalWrite(m_operatedPin, PUMP_ON);
        m_dataProvider->incrementWateringCycles();
    }
    else
    {
        digitalWrite(m_operatedPin, PUMP_OFF);
        m_dataProvider->clearWateringCycles();
    }
}

void PumpHandler::init()
{
    Logger::log(Logger::INFO, "PumpHandler - Init");
}

void PumpHandler::cyclic()
{
    Logger::log(Logger::INFO, "PumpHandler - Cyclic Task");
    handlePump();
}