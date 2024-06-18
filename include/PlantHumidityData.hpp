/*
 *   PlantHumidityData.hpp
 *   ----------------------
 *   Created on: 2024/05/30
 *   Author: Lankow
 */
#ifndef PLANT_HUMIDITY_DATA_HPP
#define PLANT_HUMIDITY_DATA_HPP

#include <Arduino.h>

class PlantHumidityData
{
public:
    PlantHumidityData(uint8_t pin, uint16_t threshold);

    uint8_t getAssignedPin() const;
    uint16_t getCurrentHumidity() const;
    uint16_t getHumidityThreshold() const;

    void setAssignedPin(const uint8_t pin);
    void setCurrentHumidity(const uint16_t humidity);
    void setHumidityThreshold(const uint16_t theshold);

private:
    uint8_t m_assignedPin;
    uint16_t m_currentHumidity;
    uint16_t m_humidityThreshold;
};

#endif // PLANT_HUMIDITY_DATA_HPP