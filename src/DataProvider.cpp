/*
*   DataProvider.cpp
*   ----------------------
*   Created on: 2023/09/29
*   Author: Lankow
*/
#include "DataProvider.hpp"

DataProvider::DataProvider(): m_currentTime(""),
                              m_temperature(0),
                              m_roomHumidity(0)
                              {
    for (int i = 0; i < 10; i++) {
    m_humidityData[i] = HumidityData();
    }
};

char* DataProvider::getCurrentTime(){
    return m_currentTime;
};

float& DataProvider::getTemperature(){
    return m_temperature;
};

float& DataProvider::getRoomHumidity(){
    return m_roomHumidity;
};

void DataProvider::setCurrentTime(char p_currentTime[]){
    if(nullptr != &p_currentTime){
        // m_currentTime = p_currentTime;
    }
};

void DataProvider::setTemperature(float p_temperature){
    if(nullptr != &p_temperature){
        m_temperature = p_temperature;
    }
};

void DataProvider::setRoomHumidity(float p_roomHumidity){
    if(nullptr != &p_roomHumidity){
        m_roomHumidity = p_roomHumidity;
    }
};

void DataProvider::setCurrentHumidityLvl(uint8_t p_handlerId, uint16_t p_readHumidity){
    if(nullptr != &p_readHumidity){
        m_humidityData[p_handlerId].setCurrentHumidityLvl(p_readHumidity);
        Serial.println(m_humidityData[p_handlerId].getCurrentHumidityLvl());
    }
};

void DataProvider::setHumidityThreshold(uint8_t p_handlerId, uint16_t p_newThreshold){
    if(nullptr != &p_newThreshold){
        m_humidityData[p_handlerId].setHumidityThreshold(p_newThreshold);
    } 
};

void DataProvider::setNeedsWatering(uint8_t p_handlerId, bool p_needsWatering){
    if(nullptr != &p_needsWatering){
        m_humidityData[p_handlerId].setNeedsWatering(p_needsWatering);
    } 
};