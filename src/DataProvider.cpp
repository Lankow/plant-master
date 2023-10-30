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

char *DataProvider::getCurrentTime()
{
    return m_currentTime;
}

HumidityData *DataProvider::getHumidityData()
{
    return m_humidityData;
}

/* SETTERS */

void DataProvider::setCurrentTime(tm timeinfo)
{
    strftime(m_currentTime, 80, "%y%m%d-%H-%M-%S", &timeinfo);
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

void DataProvider::setHumidityData(uint8_t handlerId, HumidityData humidityData)
{
    m_humidityData[handlerId] = humidityData;
}
