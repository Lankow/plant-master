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

#include "constants.hpp"
#include "HumidityData.hpp"

class DataProvider
{
public:
    DataProvider();

    float getTemperature() const;
    float getRoomHumidity() const;
    uint8_t getSensorToWater() const;

    const std::string &getCurrentTime() const;
    const std::vector<HumidityData> &getHumidityData() const;

    void setTemperature(float temperature);
    void setRoomHumidity(float roomHumidity);
    void setSensorToWater(uint8_t sensorToWaterId);
    void setCurrentTime(tm timeinfo);

    void setHandlerHumidityLvl(uint8_t handlerId, uint16_t humidityLvl);
    void setHandlerThreshold(uint8_t handlerId, uint16_t threshold);
    void setHandlerActive(uint8_t handlerId, bool isActive);

private:
    std::string m_currentTime = DEFAULT_TIME;
    float m_temperature = DEFAULT_TEMPERATURE;
    float m_roomHumidity = DEFAULT_ROOM_HUMIDITY;

    std::vector<HumidityData> m_humidityData;
    uint8_t m_sensorToWater = NO_SENSOR;
};
#endif // DATA_PROVIDER_HPP
