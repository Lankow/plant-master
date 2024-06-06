/*
 *   PlantHumidityReader.hpp
 *   ----------------------
 *   Created on: 2024/05/28
 *   Author: Lankow
 */
#ifndef PLANT_HUMIDITY_READER_HPP
#define PLANT_HUMIDITY_READER_HPP

#include <Arduino.h>
#include <memory>
#include "MQTTManager.hpp"

class PlantHumidityReader
{
public:
    PlantHumidityReader(const uint8_t pin, std::shared_ptr<MQTTManager> mqttManager);

    void cyclic();

private:
    std::shared_ptr<MQTTManager> m_mqttManager;
    uint8_t m_operatedPin;

    void readHumidity();
};

#endif // PLANT_HUMIDITY_READER_HPP