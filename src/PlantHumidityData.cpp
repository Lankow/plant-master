/*
 *   PlantHumidityData.cpp
 *   ----------------------
 *   Created on: 2024/05/30
 *   Author: Lankow
 */
#include "PlantHumidityData.hpp"
#include "Constants.hpp"

PlantHumidityData::PlantHumidityData(uint8_t pin, uint16_t threshold)
    : m_assignedPin(pin),
      m_humidityThreshold(threshold),
      m_currentHumidity(HumiditySensor::DEFAULT_HUMIDITY){};

uint8_t PlantHumidityData::getAssignedPin() const
{
    return m_assignedPin;
};

uint16_t PlantHumidityData::getCurrentHumidity() const
{
    return m_currentHumidity;
};

uint16_t PlantHumidityData::getHumidityThreshold() const
{
    return m_humidityThreshold;
};

void PlantHumidityData::setAssignedPin(const uint8_t pin)
{
    m_assignedPin = pin;
};

void PlantHumidityData::setCurrentHumidity(const uint16_t humidity)
{
    m_currentHumidity = humidity;
};

void PlantHumidityData::setHumidityThreshold(const uint16_t threshold)
{
    m_humidityThreshold = threshold;
};