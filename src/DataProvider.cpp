/*
 *   DataProvider.cpp
 *   ----------------------
 *   Created on: 2023/09/29
 *   Author: Lankow
 */
#include "DataProvider.hpp"

DataProvider::DataProvider()
    : m_currentTime(DEFAULT_TIME),
      m_temperature(0),
      m_roomHumidity(0),
      m_sensorToWater(NO_SENSOR)
{
    for (int i = 0; i < MAX_SENSORS_NO; i++)
    {
        m_humidityData[i] = HumidityData();
    }
}

/* GETTERS */

char *DataProvider::getCurrentTime()
{
    return m_currentTime;
}

float &DataProvider::getTemperature()
{
    return m_temperature;
}

float &DataProvider::getRoomHumidity()
{
    return m_roomHumidity;
}

uint8_t &DataProvider::getSensorToWater()
{
    return m_sensorToWater;
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
