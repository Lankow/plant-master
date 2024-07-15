/**
 * @file PlantHumidityHandler.hpp
 * @date   2024-05-28
 * @author Lankow
 * @version 1.0
 *
 * @brief This file contains the definition of the PlantHumidityHandler class.
 *
 * The PlantHumidityHandler class is responsible for reading humidity data from plant sensors and
 * managing the operation of valves based on the humidity readings and configuration settings.
 */
#ifndef PLANT_HUMIDITY_HANDLER_HPP
#define PLANT_HUMIDITY_HANDLER_HPP

#include <Arduino.h>
#include <memory>
#include "network/MQTTManager.hpp"
#include "config/Configurator.hpp"
#include "data/DataStorage.hpp"

class PlantHumidityHandler
{
public:
    PlantHumidityHandler(std::shared_ptr<Configurator> configurator, std::shared_ptr<MQTTManager> mqttManager, std::shared_ptr<DataStorage> dataStorage);

    void cyclic();

private:
    std::shared_ptr<MQTTManager> m_mqttManager;
    std::shared_ptr<Configurator> m_configurator;
    std::shared_ptr<DataStorage> m_dataStorage;

    void readHumidity();
    void openValve(uint16_t readerPin);
    void closeValves();
};

#endif // PLANT_HUMIDITY_HANDLER_HPP