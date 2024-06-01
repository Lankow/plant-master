/*
 *   ValveController.hpp
 *   ----------------------
 *   Created on: 2024/05/29
 *   Author: Lankow
 */
#ifndef VALVE_CONTROLLER_HPP
#define VALVE_CONTROLLER_HPP

#include <Arduino.h>

class ValveController
{
public:
    ValveController(const uint8_t pin);

    void turnOn();
    void turnOff();
    void toggle();

private:
    uint8_t m_operatedPin;
};

#endif // VALVE_CONTROLLER_HPP