/*
 *   WateringManager.hpp
 *   ----------------------
 *   Created on: 2024/06/12
 *   Author: Lankow
 */
#ifndef WATERING_MANAGER_HPP
#define WATERING_MANAGER_HPP

#include <Arduino.h>
#include <memory>
#include "DataStorage.hpp"
#include "MQTTManager.hpp"

class WateringManager
{
public:
    WateringManager(std::shared_ptr<DataStorage> dataStorage, std::shared_ptr<MQTTManager> mqttManager);

    void cyclic();

private:
    std::shared_ptr<DataStorage> m_dataStorage;
    std::shared_ptr<MQTTManager> m_mqttManager;

    bool m_waterPumpActive;
    uint16_t m_valveActive;

    void checkHumidity();
};

#endif // WATERING_MANAGER_HPP