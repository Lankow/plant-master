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

/**
 * @class WaterPumpController
 * @brief A class for controlling the water pump based on stored data.
 *
 * The WaterPumpController class manages the water pump, turning it on or off based on the
 * state stored in a DataStorage object.
 */
class WaterPumpController
{
public:
    /**
     * @brief Constructs a new WaterPumpController object.
     *
     * @param configurator A shared pointer to a Configurator object for configuration settings.
     * @param dataStorage A shared pointer to a DataStorage object for storing data and state.
     */
    WaterPumpController(std::shared_ptr<Configurator> configurator, std::shared_ptr<DataStorage> dataStorage);

    /**
     * @brief Initializes the water pump controller.
     *
     * This method initializes the pin mode for the water pump and ensures it is turned off initially.
     */
    void init();

    /**
     * @brief Periodically checks the water pump state and controls the pump.
     *
     * This method should be called cyclically to ensure that the water pump is turned on or off
     * based on the state stored in the DataStorage object.
     */
    void cyclic();

private:
    std::shared_ptr<DataStorage> m_dataStorage; /**< A shared pointer to a DataStorage object for storing data and state. */
    uint8_t m_operatedPin;                      /**< The pin number used to control the water pump. */

    /**
     * @brief Turns the water pump on.
     */
    void turnOn();

    /**
     * @brief Turns the water pump off.
     */
    void turnOff();
};

#endif // WATER_PUMP_CONTROLLER_HPP