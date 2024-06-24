/*
 *   WaterPumpController.hpp
 *   ----------------------
 *   Created on: 2024/05/29
 *   Author: Lankow
 */
#ifndef WATER_PUMP_CONTROLLER_HPP
#define WATER_PUMP_CONTROLLER_HPP

#include <Arduino.h>
#include <memory>
#include "Configurator.hpp"
#include "DataStorage.hpp"

class WaterPumpController
{
public:
    WaterPumpController(std::shared_ptr<Configurator> configurator, std::shared_ptr<DataStorage> dataStorage);

    void init();
    void cyclic();

private:
    std::shared_ptr<DataStorage> m_dataStorage;
    uint8_t m_operatedPin;

    void turnOn();
    void turnOff();
};

#endif // WATER_PUMP_CONTROLLER_HPP