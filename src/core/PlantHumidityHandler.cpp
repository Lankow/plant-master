/**
 * @file PlantHumidityHandler.cpp
 * @date   2024-05-28
 * @author Lankow
 * @version 1.0
 *
 * @brief This file contains the implementation of the PlantHumidityHandler class.
 *
 * The PlantHumidityHandler class is responsible for reading humidity data from plant sensors and
 * managing the operation of valves based on the humidity readings and configuration settings.
 */

#include "core/PlantHumidityHandler.hpp"
#include "config/Constants.hpp"

PlantHumidityHandler::PlantHumidityHandler(std::shared_ptr<Configurator> configurator, std::shared_ptr<MQTTManager> mqttManager, std::shared_ptr<DataStorage> dataStorage)
    : m_configurator(configurator),
      m_mqttManager(mqttManager),
      m_dataStorage(dataStorage) {}

void PlantHumidityHandler::cyclic()
{
    readHumidity();

#ifndef PLANT_MASTER
    if (m_dataStorage->isWaterPumpActive())
    {
        openValve(m_dataStorage->getActiveReaderPin());
    }
    else
    {
        closeValves();
    }
#endif
}

void PlantHumidityHandler::readHumidity()
{
    for (int pin : m_configurator->getReaderPins())
    {
        uint16_t humidityReading = analogRead(pin);

        if (humidityReading > HumiditySensor::AIR_HUMIDITY)
            humidityReading = HumiditySensor::AIR_HUMIDITY;

        if (humidityReading < HumiditySensor::WATER_HUMIDITY)
            humidityReading = HumiditySensor::WATER_HUMIDITY;

        uint16_t humidityValue = (HumiditySensor::AIR_HUMIDITY - humidityReading) / 14;
        Serial.println("Value:");
        Serial.println(humidityValue);
        m_mqttManager->publish(MQTT::PLANT_HUMIDITY + "/" + std::to_string(pin), std::to_string(humidityValue), 0, false);
    }
}

void PlantHumidityHandler::openValve(uint16_t readerPin)
{
    Serial.print("Opening valve: ");
    Serial.println(readerPin);
}

void PlantHumidityHandler::closeValves()
{
    Serial.println("Closing valves.");
}