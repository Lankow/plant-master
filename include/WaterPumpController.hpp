/*
 *   WaterPumpController.hpp
 *   ----------------------
 *   Created on: 2024/05/29
 *   Author: Lankow
 */
#ifndef WATER_PUMP_CONTROLLER_HPP
#define WATER_PUMP_CONTROLLER_HPP

#include <Arduino.h>

class WaterPumpController
{
    public:
        WaterPumpController(const uint8_t pin);

        void init();

    private:
        void turnOn();
        void turnOff();
        
        uint8_t m_operatedPin;
};

#endif // WATER_PUMP_CONTROLLER_HPP