/*
*   DataProvider.hpp
*   ----------------------
*   Created on: 2023/09/29
*   Author: Lankow
*/
#ifndef DATA_PROVIDER_HPP
#define DATA_PROVIDER_HPP

#include <Arduino.h>
#include "HumidityData.hpp"

// DataProvider to store all the information that could be forwarded
// Handlers have a handle on a dataProvider and on cyclics fill data
// DataManager on cyclic checks and manages the data e.g. humidity thresholds

class DataProvider
{
    private:
    HumidityData m_humidityData[10];
    char m_currentTime[20];
    float m_temperature;
    float m_roomHumidity;
    bool m_pumpActive;

    public:
    DataProvider();

    float& getTemperature();
    float& getRoomHumidity();
    char* getCurrentTime();
    
    void setCurrentTime(char p_currentTime[]);
    void setTemperature(float p_temperature);
    void setRoomHumidity(float p_roomHumidity);

    void setCurrentHumidityLvl(uint8_t p_handlerId, uint16_t p_readHumidity);
    void setHumidityThreshold(uint8_t p_handlerId, uint16_t p_newThreshold);
    void setNeedsWatering(uint8_t p_handlerId, bool p_needsWatering);
};
#endif // DATA_PROVIDER_HPP
