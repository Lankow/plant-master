/*
 *   WaterPumpController.cpp
 *   ----------------------
 *   Created on: 2024/05/29
 *   Author: Lankow
 */

#include "WaterPumpController.hpp"

WaterPumpController::WaterPumpController(const uint8_t pin): m_operatedPin(pin){};

void WaterPumpController::init(){
    pinMode(m_operatedPin, OUTPUT);
}

void WaterPumpController::turnOn(){
    digitalWrite(m_operatedPin, HIGH);
};

void WaterPumpController::turnOff(){
    digitalWrite(m_operatedPin, LOW);
};
