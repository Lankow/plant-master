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
#include "PlantHumidityData.hpp"
#include "Constants.hpp"

class DataStorage
{
    public:
    DataStorage();

    const std::vector<PlantHumidityData> &getPlantsHumidityData() const;
    float getRoomTemperature() const;
    float getRoomHumidity() const;

    void setRoomTemperature(const float roomTemperature);
    void setRoomHumidity(const float roomHumidity);
    void setPlantHumidity(const uint8_t index, const uint16_t humidity);
    void setHumidityThreshold(const uint8_t index, const uint16_t threshold);

    private:
    std::vector<PlantHumidityData> m_plantsHumidityData;
    float m_roomTemperature = DEFAULT_ROOM_TEMPERATURE;
    float m_roomHumidity = DEFAULT_ROOM_HUMIDITY;
};

#endif // DATA_STORAGE_HPP