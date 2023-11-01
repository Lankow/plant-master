/*
 *   DataProvider.cpp
 *   ----------------------
 *   Created on: 2023/09/29
 *   Author: Lankow
 */
#include "DataProvider.hpp"

DataProvider::DataProvider()
{
    for (int i = 0; i < MAX_SENSORS_NO; i++)
    {
        m_humidityData[i] = HumidityData();
    }
}

/* GETTERS */

float DataProvider::getTemperature() const
{
    return m_temperature;
}

float DataProvider::getRoomHumidity() const
{
    return m_roomHumidity;
}

uint8_t DataProvider::getSensorToWater() const
{
    return m_sensorToWater;
}

const std::string &DataProvider::getCurrentTime() const
{
    return m_currentTime;
}

const HumidityData *DataProvider::getHumidityData() const
{
    return m_humidityData;
}

/* SETTERS */

void DataProvider::setCurrentTime(tm timeinfo)
{
    // Time Lib function to be added here;
}

void DataProvider::setTemperature(float temperature)
{
    m_temperature = temperature;
}

void DataProvider::setRoomHumidity(float roomHumidity)
{
    m_roomHumidity = roomHumidity;
}

void DataProvider::setSensorToWater(uint8_t sensorToWaterId)
{
    m_sensorToWater = sensorToWaterId;
}

void DataProvider::setHandlerHumidityLvl(uint8_t handlerId, uint16_t humidityLvl)
{
    m_humidityData[handlerId].setCurrentHumidityLvl(humidityLvl);
};

void DataProvider::setHandlerThreshold(uint8_t handlerId, uint16_t threshold)
{
    m_humidityData[handlerId].setHumidityThreshold(threshold);
};

void DataProvider::setHandlerActive(uint8_t handlerId, bool isActive)
{
    m_humidityData[handlerId].setHumidityActive(isActive);
};
