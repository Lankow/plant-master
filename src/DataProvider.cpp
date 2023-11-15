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
        m_humidityData.push_back(HumidityData());
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

uint8_t DataProvider::getWateringCycles() const
{
    return m_wateringCycles;
};

std::time_t DataProvider::getCurrentTime() const
{
    return m_currentTime;
}

const std::vector<HumidityData> &DataProvider::getHumidityData() const
{
    return m_humidityData;
}

/* SETTERS */

void DataProvider::setCurrentTime(const std::time_t time)
{
    m_currentTime = time;
}

void DataProvider::setTemperature(const float temperature)
{
    m_temperature = temperature;
}

void DataProvider::setRoomHumidity(const float roomHumidity)
{
    m_roomHumidity = roomHumidity;
}

void DataProvider::setSensorToWater(const uint8_t sensorToWaterId)
{
    m_sensorToWater = sensorToWaterId;
}

void DataProvider::setHandlerHumidityLvl(const uint8_t handlerId, const uint16_t humidityLvl)
{
    m_humidityData[handlerId].setCurrentHumidityLvl(humidityLvl);
};

void DataProvider::setHandlerThreshold(const uint8_t handlerId, const uint16_t threshold)
{
    m_humidityData[handlerId].setHumidityThreshold(threshold);
};

void DataProvider::setHandlerActive(const uint8_t handlerId, const bool isActive)
{
    m_humidityData[handlerId].setHumidityActive(isActive);
};

void DataProvider::incrementWateringCycles()
{
    m_sensorToWater++;
}

void DataProvider::clearWateringCycles()
{
    m_sensorToWater = 0;
}