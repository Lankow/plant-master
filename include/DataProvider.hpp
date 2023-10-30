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

    float getTemperature() const;
    float getRoomHumidity() const;
    uint8_t getSensorToWater() const;

    char *getCurrentTime();
    HumidityData *getHumidityData();

    void setTemperature(float temperature);
    void setRoomHumidity(float roomHumidity);
    void setSensorToWater(uint8_t sensorToWaterId);

    void setCurrentTime(tm timeinfo);
    void setHumidityData(uint8_t handlerId, HumidityData humidityData);

private:
    char m_currentTime[TIMESTAMP_LENGTH] = DEFAULT_TIME;
    float m_temperature = DEFAULT_TEMPERATURE;
    float m_roomHumidity = DEFAULT_ROOM_HUMIDITY;

    HumidityData m_humidityData[MAX_SENSORS_NO];
    uint8_t m_sensorToWater = NO_SENSOR;
};
#endif // DATA_PROVIDER_HPP
