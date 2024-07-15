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

class WateringManager
{
public:
    WateringManager(std::shared_ptr<DataStorage> dataStorage, std::shared_ptr<MQTTManager> mqttManager);

    void cyclic();

private:
    std::shared_ptr<DataStorage> m_dataStorage;
    std::shared_ptr<MQTTManager> m_mqttManager;

    void checkHumidity();
};

#endif // WATERING_MANAGER_HPP