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

void DataProvider::setCurrentTime(tm p_timeinfo)
{
    strftime(m_currentTime, 80, "%y%m%d-%H-%M-%S", &p_timeinfo);
}

void DataProvider::setTemperature(float p_temperature)
{
    m_temperature = p_temperature;
}

void DataProvider::setRoomHumidity(float p_roomHumidity)
{
    m_roomHumidity = p_roomHumidity;
}

void DataProvider::setSensorToWater(uint8_t p_sensorToWaterId)
{
    m_sensorToWater = p_sensorToWaterId;
}

void DataProvider::setHumidityData(uint8_t p_handlerId, HumidityData p_humidityData)
{
    m_humidityData[p_handlerId] = p_humidityData;
}
