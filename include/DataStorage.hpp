/*
 *   DataStorage.hpp
 *   ----------------------
 *   Created on: 2024/05/30
 *   Author: Lankow
 */
#ifndef DATA_STORAGE_HPP
#define DATA_STORAGE_HPP

#include <Arduino.h>
#include <vector>
#include <memory>
#include "PlantHumidityData.hpp"
#include "Configurator.hpp"
#include "Constants.hpp"

class DataStorage
{
public:
#ifdef PLANT_MASTER
    DataStorage(std::shared_ptr<Configurator> configurator);

    const std::vector<PlantHumidityData> &getPlantsHumidityData() const;
    float getRoomTemperature() const;
    float getRoomHumidity() const;

    void setRoomTemperature(const float roomTemperature);
    void setRoomHumidity(const float roomHumidity);
    void setPlantHumidity(const uint8_t pin, const uint16_t humidity);
    void setHumidityThreshold(const uint8_t pin, const uint16_t threshold);
#else
    DataStorage();

    bool getIsWaterPumpActive() const;
    uint8_t getActiveReaderPin() const;

    void setIsWaterPumpActive(const bool isWaterPumpActive);
    void setActiveReaderPin(const uint8_t activeReaderPin);
#endif
private:
#ifdef PLANT_MASTER
    std::shared_ptr<Configurator> m_configurator;
    std::vector<PlantHumidityData> m_plantsHumidityData;
    float m_roomTemperature = DEFAULT_ROOM_TEMPERATURE;
    float m_roomHumidity = DEFAULT_ROOM_HUMIDITY;
#else
    bool m_isWaterPumpActive;
    uint8_t m_activeReaderPin;
#endif
};

#endif // DATA_STORAGE_HPP