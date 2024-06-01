/*
 *   PlantHumidityData.cpp
 *   ----------------------
 *   Created on: 2024/05/30
 *   Author: Lankow
 */
#include "PlantHumidityData.hpp"

PlantHumidityData::PlantHumidityData(){};

uint16_t PlantHumidityData::getCurrentHumidity() const
{
    return m_currentHumidity;
};

uint16_t PlantHumidityData::getHumidityThreshold() const
{
    return m_humidityThreshold;
};

void PlantHumidityData::setCurrentHumidity(const uint16_t humidity)
{
    m_currentHumidity = humidity;
};

void PlantHumidityData::setHumidityThreshold(const uint16_t threshold)
{
    m_humidityThreshold = threshold;
};