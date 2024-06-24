/*
 *   PlantHumidityHandler.cpp
 *   ----------------------
 *   Created on: 2024/05/28
 *   Author: Lankow
 */
#include "PlantHumidityHandler.hpp"
#include "Constants.hpp"

PlantHumidityHandler::PlantHumidityHandler(std::shared_ptr<Configurator> configurator, std::shared_ptr<MQTTManager> mqttManager, std::shared_ptr<DataStorage> dataStorage)
    : m_configurator(configurator),
      m_mqttManager(mqttManager),
      m_dataStorage(dataStorage){};

void PlantHumidityHandler::cyclic()
{
    readHumidity();

#ifndef PLANT_MASTER
    if (m_dataStorage->getIsWaterPumpActive())
    {
        openValve(m_dataStorage->getActiveReaderPin());
    }
    else
    {
        closeValves();
    }
#endif
}

void PlantHumidityHandler::openValve(uint16_t readerPin)
{
    Serial.println("Opening valve:");
    Serial.println(readerPin);
}

void PlantHumidityHandler::closeValves()
{
    Serial.println("Closing valves.");
}

void PlantHumidityHandler::readHumidity()
{
    for (int pin : m_configurator->getReaderPins())
    {
        uint16_t humidity = analogRead(pin);
        Serial.println(humidity);
        m_mqttManager->publish(MQTT_PLANT_HUMIDITY + "/" + std::to_string(pin), std::to_string(humidity), 0, false);
    }
}