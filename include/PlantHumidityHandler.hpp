/*
 *   PlantHumidityHandler.hpp
 *   ----------------------
 *   Created on: 2024/05/28
 *   Author: Lankow
 */
#ifndef PLANT_HUMIDITY_HANDLER_HPP
#define PLANT_HUMIDITY_HANDLER_HPP

#include <Arduino.h>
#include <memory>
#include "MQTTManager.hpp"
#include "Configurator.hpp"
#include "DataStorage.hpp"

class PlantHumidityHandler
{
public:
    PlantHumidityHandler(std::shared_ptr<Configurator> configurator, std::shared_ptr<MQTTManager> mqttManager, std::shared_ptr<DataStorage> dataStorage);

    void cyclic();

private:
    void readHumidity();
    void openValve(uint16_t readerPin);
    void closeValves();

    std::shared_ptr<MQTTManager> m_mqttManager;
    std::shared_ptr<Configurator> m_configurator;
    std::shared_ptr<DataStorage> m_dataStorage;
};

#endif // PLANT_HUMIDITY_HANDLER_HPP