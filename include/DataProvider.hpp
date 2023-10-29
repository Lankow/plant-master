/*
 *   DataProvider.hpp
 *   ----------------------
 *   Created on: 2023/09/29
 *   Author: Lankow
 */
#ifndef DATA_PROVIDER_HPP
#define DATA_PROVIDER_HPP

#include <Arduino.h>
#include "constants.hpp"
#include "HumidityData.hpp"

class DataProvider
{
public:
    DataProvider();

    float &getTemperature();
    float &getRoomHumidity();
    char *getCurrentTime();

    HumidityData *getHumidityData();
    uint8_t &getSensorToWater();

    void setCurrentTime(tm timeinfo);
    void setTemperature(float temperature);
    void setRoomHumidity(float roomHumidity);

    void setHumidityData(uint8_t handlerId, HumidityData humidityData);
    void setSensorToWater(uint8_t sensorToWaterId);

private:
    char m_currentTime[TIMESTAMP_LENGTH];
    float m_temperature;
    float m_roomHumidity;

    HumidityData m_humidityData[MAX_SENSORS_NO];
    uint8_t m_sensorToWater;
};
#endif // DATA_PROVIDER_HPP
