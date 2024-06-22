/*
 *   WaterPumpController.cpp
 *   ----------------------
 *   Created on: 2024/05/29
 *   Author: Lankow
 */

#include "WaterPumpController.hpp"

WaterPumpController::WaterPumpController(std::shared_ptr<Configurator> configurator) : m_operatedPin(configurator->getWaterPumpPin()){};

void WaterPumpController::init()
{
    pinMode(m_operatedPin, OUTPUT);
    turnOff();
}

void WaterPumpController::turnOn()
{
    digitalWrite(m_operatedPin, HIGH);
};

void WaterPumpController::turnOff()
{
    digitalWrite(m_operatedPin, LOW);
};
