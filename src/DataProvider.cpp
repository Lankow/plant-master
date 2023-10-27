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
        m_currentHumidityLvl[i] = ANALOG_PIN_MAX;
        m_humidityThreshold[i] = ANALOG_PIN_MAX;
        m_humidityActive[i] = false;
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

uint16_t *DataProvider::getCurrentHumidityLvl()
{
    return m_currentHumidityLvl;
}

uint16_t *DataProvider::getHumidityThreshold()
{
    return m_humidityThreshold;
}

bool *DataProvider::getHumidityActive()
{
    return m_humidityActive;
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

void DataProvider::setCurrentHumidityLvl(uint8_t p_handlerId, uint16_t p_readHumidity)
{
    m_currentHumidityLvl[p_handlerId] = p_readHumidity;
}

void DataProvider::setHumidityThreshold(uint8_t p_handlerId, uint16_t p_newThreshold)
{
    m_humidityThreshold[p_handlerId] = p_newThreshold;
}

void DataProvider::setHumidityActive(uint8_t p_handlerId, bool p_humidityState)
{
    m_humidityActive[p_handlerId] = p_humidityState;
}