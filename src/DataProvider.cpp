/*
*   DataProvider.cpp
*   ----------------------
*   Created on: 2023/09/29
*   Author: Lankow
*/
#include "DataProvider.hpp"

DataProvider::DataProvider(): m_currentTime(""),
                              m_temperature(0),
                              m_roomHumidity(0),
                              m_sensorToWater(NO_SENSOR)
                              {
    for (int i = 0; i < MAX_SENSORS_NO; i++) {
    m_currentHumidityLvl[i] = ANALOG_PIN_MAX;
    m_humidityThreshold[i] = ANALOG_PIN_MAX;
    }
};

/* GETTERS */

char* DataProvider::getCurrentTime(){
    return m_currentTime;
};

float& DataProvider::getTemperature(){
    return m_temperature;
};

float& DataProvider::getRoomHumidity(){
    return m_roomHumidity;
};

uint8_t&  DataProvider::getSensorToWater(){

};

uint16_t* DataProvider::getCurrentHumidityLvl(){

};

uint16_t* DataProvider::getHumidityThreshold(){

};

/* SETTERS */

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
        m_currentHumidityLvl[p_handlerId] = p_readHumidity;
    }
};

void DataProvider::setHumidityThreshold(uint8_t p_handlerId, uint16_t p_newThreshold){
    if(nullptr != &p_newThreshold){
        m_humidityThreshold[p_handlerId] = p_newThreshold;
    } 
};

void DataProvider::setSensorToWater(uint8_t p_sensorToWaterId){
    if(nullptr != &p_sensorToWaterId){
        m_sensorToWater = p_sensorToWaterId;
    } 
};