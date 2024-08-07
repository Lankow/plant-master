/**
 * @file DataStorage.cpp
 * @date   2024-05-30
 * @author Lankow
 * @version 1.0
 *
 * @brief This file contains the implementation of the DataStorage class.
 *
 * This class handles the storage and management of data related to plants, room conditions,
 * and the water pump state.
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
        uint16_t threshold =
            thresholds[i] > HumiditySensor::MAX_THRESHOLD || thresholds[i] < HumiditySensor::MIN_THRESHOLD
                ? HumiditySensor::MAX_THRESHOLD
                : thresholds[i];

        m_plantsHumidityData.emplace_back(pins[i], threshold);
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
    if (threshold > HumiditySensor::MAX_THRESHOLD || threshold < HumiditySensor::MIN_THRESHOLD)
    {
        Serial.println("Requested Humidity threshold update failed. Invalid value.");
        return;
    }

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