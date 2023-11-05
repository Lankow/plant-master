/*
 *   PumpHandler.cpp
 *   ----------------------
 *   Created on: 2023/10/10
 *   Author: Lankow
 */
#include "handler/PumpHandler.hpp"
#include "Logger.hpp"
#include "constants.hpp"

PumpHandler::PumpHandler(const uint8_t pin) : m_operatedPin(pin){};

void PumpHandler::handlePump()
{
    uint8_t sensorToWater = m_dataProvider->getSensorToWater();

    if (sensorToWater != NO_SENSOR)
    {
        analogWrite(m_operatedPin, PUMP_ON);
    }
    else
    {
        analogWrite(m_operatedPin, PUMP_OFF);
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