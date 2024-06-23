/*
 *   PlantHumidityHandler.cpp
 *   ----------------------
 *   Created on: 2024/05/28
 *   Author: Lankow
 */
#include "PlantHumidityHandler.hpp"
#include "Constants.hpp"

PlantHumidityHandler::PlantHumidityHandler(std::shared_ptr<Configurator> configurator, std::shared_ptr<MQTTManager> mqttManager)
    : m_configurator(configurator),
      m_mqttManager(mqttManager){};

void PlantHumidityHandler::cyclic()
{
    readHumidity();
}

void PlantHumidityHandler::openValve(uint16_t readerPin)
{
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