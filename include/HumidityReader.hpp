/*
 *   HumidityReader.hpp
 *   ----------------------
 *   Created on: 2024/05/28
 *   Author: Lankow
 */
#ifndef HUMIDITY_READER_HPP
#define HUMIDITY_READER_HPP

#include <Arduino.h>

class HumidityReader
{
    public:
    HumidityReader(const uint8_t pin);
    void readHumidity();

    private:
    uint8_t m_operatedPin;
};

#endif // HUMIDITY_READER_HPP