/*
 *   DHTReader.hpp
 *   ----------------------
 *   Created on: 2024/05/28
 *   Author: Lankow
 */
#ifndef DHT_READER_HPP
#define DHT_READER_HPP

#include <Arduino.h>
#include <DHT.h>

class DHTReader
{
    public:
        DHTReader(const uint8_t pin);

        void readRoomTemperature();
        void readRoomHumidity();
    private:
        DHT m_dht;
};

#endif // DHT_READER_HPP