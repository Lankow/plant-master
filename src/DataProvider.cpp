/*
*   DataProvider.cpp
*   ----------------------
*   Created on: 2023/09/29
*   Author: Lankow
*/
#include "DataProvider.hpp"

DataProvider::DataProvider(HumidityHandler *p_humidityHandler, NetworkHandler *p_networkHandler, TimeHandler *p_timeHandler) {
    m_humidityHandler = p_humidityHandler;
    m_networkHandler = p_networkHandler;
    m_timeHandler = p_timeHandler;
}

int DataProvider::getHumidity() {
    return m_humidityHandler->getCurrentHumidity();
}

String DataProvider::getTime() {
    char time_temp[20];
    m_timeHandler->getTimeStamp(time_temp);
    return time_temp;
}

void DataProvider::setThreshold(int threshold) {
    return m_humidityHandler->setHumidityThreshold(threshold);
}