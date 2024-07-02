/*
 *   WaterPumpController.cpp
 *   ----------------------
 *   Created on: 2024/05/29
 *   Author: Lankow
 */

#include "WaterPumpController.hpp"

WaterPumpController::WaterPumpController(std::shared_ptr<Configurator> configurator, std::shared_ptr<DataStorage> dataStorage)
    : m_operatedPin(configurator->getWaterPumpPin()),
      m_dataStorage(dataStorage) {}

void WaterPumpController::init()
{
    pinMode(m_operatedPin, OUTPUT);
    turnOff();
}

void WaterPumpController::cyclic()
{
    if (m_dataStorage->isWaterPumpActive())
    {
        turnOn();
    }
    else
    {
        turnOff();
    }
}

void WaterPumpController::turnOn()
{
    digitalWrite(m_operatedPin, HIGH);
}

void WaterPumpController::turnOff()
{
    digitalWrite(m_operatedPin, LOW);
}