/*
 *   HumidityHandler.cpp
 *   ----------------------
 *   Created on: 2023/09/26
 *   Author: Lankow
 */
#include "handler/HumidityHandler.hpp"
#include "constants.hpp"
#include "Logger.hpp"

static uint8_t m_idCounter;

HumidityHandler::HumidityHandler(uint8_t operatedPin)
    : m_operatedPin(operatedPin), m_handlerId(m_idCounter++){};

void HumidityHandler::handleHumidity()
{
    uint16_t result = analogRead(m_operatedPin);

    if (result != ANALOG_PIN_MAX)
    {
        m_dataProvider->getHumidityData()[m_handlerId].setCurrentHumidityLvl(result);
        m_dataProvider->getHumidityData()[m_handlerId].setHumidityActive(true);
    }
    else
    {
        m_dataProvider->getHumidityData()[m_handlerId].setHumidityActive(false);
    }
}

void HumidityHandler::init()
{
    m_logger->log(Logger::INFO, "HumidityHandler - Init");
}

void HumidityHandler::cyclic()
{
    m_logger->log(Logger::INFO, "HumidityHandler - Cyclic Task");
    handleHumidity();
}
