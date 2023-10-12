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

class DataProvider
{
    private:
    uint16_t m_currentHumidityLvl[MAX_SENSORS_NO];
    uint16_t m_humidityThreshold[MAX_SENSORS_NO];
    uint8_t m_sensorToWater;

    char m_currentTime[20];
    float m_temperature;
    float m_roomHumidity;

    public:
    DataProvider();

    float& getTemperature();
    float& getRoomHumidity();
    char* getCurrentTime();
    uint8_t& getSensorToWater();
    uint16_t* getCurrentHumidityLvl();
    uint16_t* getHumidityThreshold();

    void setCurrentTime(char p_currentTime[]);
    void setTemperature(float p_temperature);
    void setRoomHumidity(float p_roomHumidity);

    void setCurrentHumidityLvl(uint8_t p_handlerId, uint16_t p_readHumidity);
    void setHumidityThreshold(uint8_t p_handlerId, uint16_t p_newThreshold);
    void setSensorToWater(uint8_t p_sensorToWaterId);
};
#endif // DATA_PROVIDER_HPP
