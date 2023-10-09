/*
*   DataProvider.cpp
*   ----------------------
*   Created on: 2023/09/29
*   Author: Lankow
*/
#include "DataProvider.hpp"

DataProvider::DataProvider(): m_currentHumidityLvl(0),
                              m_humidityThreshold(0),
                              m_needsWatering(false),
                              m_currentTime(""),
                              m_temperature(0),
                              m_roomHumidity(0)
                              {}

int& DataProvider::getCurrentHumidityLvl(){
    return m_currentHumidityLvl;
};

int& DataProvider::getHumidityThreshold(){
    return m_humidityThreshold;
};

bool& DataProvider::getNeedsWatering(){
    return m_needsWatering;
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

void DataProvider::setCurrentHumidityLvl(int p_currentHumidityLvl){
    if(nullptr != &p_currentHumidityLvl){
        m_currentHumidityLvl = p_currentHumidityLvl;
    }
};

void DataProvider::setHumidityThreshold(int p_humidityThreshold){
    if(nullptr != &p_humidityThreshold){
        m_humidityThreshold = p_humidityThreshold;
    }
};

void DataProvider::setNeedsWatering(bool p_needsWatering){
    if(nullptr != &p_needsWatering){
        m_needsWatering = p_needsWatering;
    }
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