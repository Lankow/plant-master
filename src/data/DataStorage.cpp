/*
 *   DataStorage.cpp
 *   ----------------------
 *   Created on: 2024/05/30
 *   Author: Lankow
 */
#include "data/DataStorage.hpp"

#ifdef PLANT_MASTER
DataStorage::DataStorage(std::shared_ptr<Configurator> configurator)
    : m_configurator(configurator),
      m_isWaterPumpActive(false),
      m_activeReaderPin(HumiditySensor::DEFAULT_ACTIVE_PIN),
      m_roomTemperature(Room::DEFAULT_TEMPERATURE),
      m_roomHumidity(Room::DEFAULT_HUMIDITY)
{
    auto pins = configurator->getReaderPins();
    auto thresholds = configurator->getThresholds();

    for (size_t i = 0; i < pins.size(); ++i)
    {
        m_plantsHumidityData.emplace_back(pins[i], thresholds[i]);
    }
}
#else
DataStorage::DataStorage()
    : m_isWaterPumpActive(false),
      m_activeReaderPin(HumiditySensor::DEFAULT_ACTIVE_PIN) {}
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

void DataStorage::setRoomTemperature(float roomTemperature)
{
    m_roomTemperature = roomTemperature;
}

void DataStorage::setRoomHumidity(float roomHumidity)
{
    m_roomHumidity = roomHumidity;
}

void DataStorage::setPlantHumidity(uint8_t pin, uint16_t humidity)
{
    for (auto &plant : m_plantsHumidityData)
    {
        if (plant.getAssignedPin() == pin)
        {
            plant.setCurrentHumidity(humidity);
            break;
        }
    }
}

void DataStorage::setHumidityThreshold(uint8_t pin, uint16_t threshold)
{
    for (size_t i = 0; i < m_plantsHumidityData.size(); ++i)
    {
        if (m_plantsHumidityData[i].getAssignedPin() == pin)
        {
            m_plantsHumidityData[i].setHumidityThreshold(threshold);
            m_configurator->updateThreshold(i, threshold);
            break;
        }
    }
}
#endif

bool DataStorage::isWaterPumpActive() const
{
    return m_isWaterPumpActive;
}

uint8_t DataStorage::getActiveReaderPin() const
{
    return m_activeReaderPin;
}

void DataStorage::setWaterPumpActive(bool isWaterPumpActive)
{
    m_isWaterPumpActive = isWaterPumpActive;
}

void DataStorage::setActiveReaderPin(uint8_t activeReaderPin)
{
    m_activeReaderPin = activeReaderPin;
}