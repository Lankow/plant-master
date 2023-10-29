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

    void setCurrentTime(tm p_timeinfo);
    void setTemperature(float p_temperature);
    void setRoomHumidity(float p_roomHumidity);

    void setHumidityData(uint8_t p_handlerId, HumidityData p_humidityData);
    void setSensorToWater(uint8_t p_sensorToWaterId);

private:
    char m_currentTime[TIMESTAMP_LENGTH];
    float m_temperature;
    float m_roomHumidity;

    HumidityData m_humidityData[MAX_SENSORS_NO];
    uint8_t m_sensorToWater;
};
#endif // DATA_PROVIDER_HPP
