/*
 *   DataStorage.cpp
 *   ----------------------
 *   Created on: 2024/05/30
 *   Author: Lankow
 */
#include "DataStorage.hpp"

#ifdef PLANT_MASTER
DataStorage::DataStorage(std::shared_ptr<Configurator> configurator)
{
    std::vector<int> pins = configurator->getReaderPins();
    std::vector<int> thresholds = configurator->getThresholds();

    for (int i = 0; i < pins.size(); i++)
    {
        m_plantsHumidityData.push_back(PlantHumidityData(pins[i], thresholds[i]));
    }
};

#endif
float DataStorage::getRoomHumidity() const
{
    return m_roomHumidity;
}

float DataStorage::getRoomTemperature() const
{
    return m_roomTemperature;
}

const std::vector<PlantHumidityData> &DataStorage::getPlantsHumidityData() const
{
    return m_plantsHumidityData;
}

void DataStorage::setRoomTemperature(const float roomTemperature)
{
    m_roomTemperature = roomTemperature;
}

void DataStorage::setRoomHumidity(const float roomHumidity)
{
    m_roomHumidity = roomHumidity;
}

void DataStorage::setPlantHumidity(const uint8_t pin, const uint16_t humidity)
{
    for (int i = 0; i < m_plantsHumidityData.size(); i++)
    {
        if (m_plantsHumidityData[i].getAssignedPin() == pin)
        {
            m_plantsHumidityData[i].setCurrentHumidity(humidity);
        }
    }
};

void DataStorage::setHumidityThreshold(const uint8_t pin, const uint16_t threshold)
{
    for (int i = 0; i < m_plantsHumidityData.size(); i++)
    {
        if (m_plantsHumidityData[i].getAssignedPin() == pin)
        {
            m_plantsHumidityData[i].setHumidityThreshold(threshold);
        }
    }
};