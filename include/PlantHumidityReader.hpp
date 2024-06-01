/*
 *   PlantHumidityReader.hpp
 *   ----------------------
 *   Created on: 2024/05/28
 *   Author: Lankow
 */
#ifndef PLANT_HUMIDITY_READER_HPP
#define PLANT_HUMIDITY_READER_HPP

#include <Arduino.h>

class PlantHumidityReader
{
public:
    PlantHumidityReader(const uint8_t pin);

    void readHumidity();

private:
    uint8_t m_operatedPin;
};

#endif // PLANT_HUMIDITY_READER_HPP