/*
 *   PlantHumidityData.hpp
 *   ----------------------
 *   Created on: 2024/05/30
 *   Author: Lankow
 */
#ifndef PLANT_HUMIDITY_DATA_HPP
#define PLANT_HUMIDITY_DATA_HPP

#include <Arduino.h>
#include "Constants.hpp"

class PlantHumidityData
{
public:
    PlantHumidityData();

    uint16_t getCurrentHumidity() const;
    uint16_t getHumidityThreshold() const;

    void setCurrentHumidity(const uint16_t humidity);
    void setHumidityThreshold(const uint16_t theshold);

private:
    uint16_t m_currentHumidity = DEFAULT_HUMIDITY;
    uint16_t m_humidityThreshold = DEFAULT_HUMIDITY_THRESHOLD;
};

#endif // PLANT_HUMIDITY_DATA_HPP