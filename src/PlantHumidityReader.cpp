/*
 *   PlantHumidityReader.cpp
 *   ----------------------
 *   Created on: 2024/05/28
 *   Author: Lankow
 */
#include "PlantHumidityReader.hpp"
#include "Constants.hpp"

PlantHumidityReader::PlantHumidityReader(std::shared_ptr<Configurator> configurator, std::shared_ptr<MQTTManager> mqttManager)
    : m_configurator(configurator),
      m_mqttManager(mqttManager){};

void PlantHumidityReader::cyclic()
{
    readHumidity();
}

void PlantHumidityReader::readHumidity()
{
    for (int pin : m_configurator->getReaderPins())
    {
        uint16_t humidity = analogRead(pin);
        Serial.println(humidity);
        m_mqttManager->publish(MQTT_PLANT_HUMIDITY + "/" + std::to_string(pin), std::to_string(humidity), 0, false);
    }
}