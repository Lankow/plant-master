/**
 * @file PlantHumidityData.hpp
 * @date   2024-05-30
 * @author Lankow
 * @version 1.0
 *
 * @brief This file contains the definition of the PlantHumidityData class.
 *
 * Stores information about the humidity of a plant, including its assigned pin,
 * current humidity, and humidity threshold.
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

    void setAssignedPin(uint8_t pin);
    void setCurrentHumidity(uint16_t humidity);
    void setHumidityThreshold(uint16_t threshold);

private:
    uint8_t m_assignedPin;
    uint16_t m_currentHumidity;
    uint16_t m_humidityThreshold;
};

#endif // PLANT_HUMIDITY_DATA_HPP