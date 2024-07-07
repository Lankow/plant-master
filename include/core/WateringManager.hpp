/**
 * @file WateringManager.hpp
 * @date   2024-06-12
 * @author Lankow
 * @version 1.0
 *
 * @brief This file contains the definition of the WateringManager class.
 *
 * The WateringManager class is responsible for managing the watering process by checking
 * humidity levels and controlling the water pump based on the humidity data.
 */
#ifndef WATERING_MANAGER_HPP
#define WATERING_MANAGER_HPP

#include <Arduino.h>
#include <memory>
#include "data/DataStorage.hpp"
#include "network/MQTTManager.hpp"

/**
 * @class WateringManager
 * @brief A class for managing the watering process based on plant humidity data.
 *
 * The WateringManager class checks the humidity levels of plants and activates the water pump
 * if the humidity falls below a certain threshold.
 */
class WateringManager
{
public:
    /**
     * @brief Constructs a new WateringManager object.
     *
     * @param dataStorage A shared pointer to a DataStorage object for storing data and state.
     * @param mqttManager A shared pointer to an MQTTManager object for managing MQTT communication.
     */
    WateringManager(std::shared_ptr<DataStorage> dataStorage, std::shared_ptr<MQTTManager> mqttManager);

    /**
     * @brief Periodically checks plant humidity and controls the water pump.
     *
     * This method should be called cyclically to ensure that plant humidity is checked and
     * the water pump is controlled at regular intervals.
     */
    void cyclic();

private:
    std::shared_ptr<DataStorage> m_dataStorage; /**< A shared pointer to a DataStorage object for storing data and state. */
    std::shared_ptr<MQTTManager> m_mqttManager; /**< A shared pointer to an MQTTManager object for managing MQTT communication. */

    /**
     * @brief Checks the humidity levels of plants and activates the water pump if needed.
     *
     * This method checks the humidity levels of plants and activates the water pump if any plant's
     * humidity falls below its threshold.
     */
    void checkHumidity();
};

#endif // WATERING_MANAGER_HPP