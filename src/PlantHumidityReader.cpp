/*
 *   PlantHumidityReader.cpp
 *   ----------------------
 *   Created on: 2024/05/28
 *   Author: Lankow
 */
#include "PlantHumidityReader.hpp"
#include "Constants.hpp"

PlantHumidityReader::PlantHumidityReader(const uint8_t pin, std::shared_ptr<MQTTManager> mqttManager)
    : m_operatedPin(pin),
      m_mqttManager(mqttManager){};

void PlantHumidityReader::cyclic()
{
    readHumidity();
}

void PlantHumidityReader::readHumidity()
{
    uint16_t humidity = analogRead(m_operatedPin);
    m_mqttManager->publish(MQTT_PLANT_HUMIDITY, std::to_string(humidity), 0, false);
}