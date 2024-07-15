/**
 * @file WaterPumpController.hpp
 * @date   2024-05-29
 * @author Lankow
 * @version 1.0
 *
 * @brief This file contains the definition of the WaterPumpController class.
 *
 * The WaterPumpController class is responsible for controlling the water pump based on the data
 * stored in the DataStorage object. It turns the pump on or off based on the state of the water pump.
 */
#ifndef WATER_PUMP_CONTROLLER_HPP
#define WATER_PUMP_CONTROLLER_HPP

#include <Arduino.h>
#include <memory>
#include "config/Configurator.hpp"
#include "data/DataStorage.hpp"

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