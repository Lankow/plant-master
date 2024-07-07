/**
 * @file WaterPumpController.cpp
 * @date   2024-05-29
 * @author Lankow
 * @version 1.0
 *
 * @brief This file contains the implementation of the WaterPumpController class.
 *
 * The WaterPumpController class is responsible for controlling the water pump based on the data
 * stored in the DataStorage object. It turns the pump on or off based on the state of the water pump.
 */

#include "core/WaterPumpController.hpp"

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