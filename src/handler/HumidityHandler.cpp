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

HumidityHandler::HumidityHandler(uint8_t p_operatedPin)
    : m_operatedPin(p_operatedPin), m_handlerId(m_idCounter++) {}

void HumidityHandler::handleHumidity()
{
    auto dataProvider = getDataProvider();
    if (!dataProvider)
    {
        return; // Exit early if dataProvider is nullptr
    }

    uint16_t result = analogRead(m_operatedPin);

    if (result != ANALOG_PIN_MAX)
    {
        dataProvider->setCurrentHumidityLvl(m_handlerId, result);
        dataProvider->setHumidityActive(m_handlerId, true);
    }
    else
    {
        dataProvider->setHumidityActive(m_handlerId, false);
    }
}

void HumidityHandler::cyclic()
{
    getLogger()->log(Logger::INFO, "HumidityHandler - Cyclic Task");
    handleHumidity();
}
