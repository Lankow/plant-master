/*
 *   DataProvider.hpp
 *   ----------------------
 *   Created on: 2023/09/29
 *   Author: Lankow
 */
#ifndef DATA_PROVIDER_HPP
#define DATA_PROVIDER_HPP

#include <Arduino.h>
#include <vector>
#include <chrono>

#include "constants.hpp"
#include "HumidityData.hpp"

class DataProvider
{
public:
    DataProvider();

    float getTemperature() const;
    float getRoomHumidity() const;
    uint8_t getSensorToWater() const;
    uint8_t getWateringCycles() const;

    const std::vector<HumidityData> &getHumidityData() const;

    void setTemperature(const float temperature);
    void setRoomHumidity(const float roomHumidity);
    void setSensorToWater(const uint8_t sensorToWaterId);
    void setCurrentTime(const std::time_t currentTime);

    void setHandlerHumidityLvl(const uint8_t handlerId, const uint16_t humidityLvl);
    void setHandlerThreshold(const uint8_t handlerId, const uint16_t threshold);
    void setHandlerActive(const uint8_t handlerId, const bool isActive);

    void incrementWateringCycles();
    void clearWateringCycles();

private:
    float m_temperature = DEFAULT_TEMPERATURE;
    float m_roomHumidity = DEFAULT_ROOM_HUMIDITY;

    std::vector<HumidityData> m_humidityData;
    uint8_t m_sensorToWater = NO_SENSOR;
    uint8_t m_wateringCycles = DEFAULT_CYCLES;
};
#endif // DATA_PROVIDER_HPP
