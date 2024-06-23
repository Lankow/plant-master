/*
 *   DataStorage.cpp
 *   ----------------------
 *   Created on: 2024/05/30
 *   Author: Lankow
 */
#include "DataStorage.hpp"

#ifdef PLANT_MASTER
DataStorage::DataStorage(std::shared_ptr<Configurator> configurator) : m_configurator(configurator)
{
    std::vector<int> pins = configurator->getReaderPins();
    std::vector<int> thresholds = configurator->getThresholds();

    for (int i = 0; i < pins.size(); i++)
    {
        m_plantsHumidityData.push_back(PlantHumidityData(pins[i], thresholds[i]));
    }
};
#else
DataStorage::DataStorage() : m_isWaterPumpActive(false), m_activeReaderPin(DEFAULT_ACTIVE_READER_PIN){};
#endif

#ifdef PLANT_MASTER
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
            m_configurator->updateThreshold(i, threshold);
        }
    }
};
#else
bool DataStorage::getIsWaterPumpActive() const
{
    return m_isWaterPumpActive;
}

uint8_t DataStorage::getActiveReaderPin() const
{
    return m_activeReaderPin;
}

void DataStorage::setIsWaterPumpActive(const bool isWaterPumpActive)
{
    m_isWaterPumpActive = isWaterPumpActive;
}

void DataStorage::setActiveReaderPin(const uint8_t activeReaderPin)
{
    m_activeReaderPin = activeReaderPin;
}
#endif