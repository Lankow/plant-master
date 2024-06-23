/*
 *   PlantHumidityHandler.hpp
 *   ----------------------
 *   Created on: 2024/05/28
 *   Author: Lankow
 */
#ifndef PLANT_HUMIDITY_READER_HPP
#define PLANT_HUMIDITY_READER_HPP

#include <Arduino.h>
#include <memory>
#include "MQTTManager.hpp"
#include "Configurator.hpp"

class PlantHumidityHandler
{
public:
    PlantHumidityHandler(std::shared_ptr<Configurator> configurator, std::shared_ptr<MQTTManager> mqttManager);

    void cyclic();
    void openValve(uint16_t readerPin);

private:
    std::shared_ptr<MQTTManager> m_mqttManager;
    std::shared_ptr<Configurator> m_configurator;

    void readHumidity();
};

#endif // PLANT_HUMIDITY_READER_HPP