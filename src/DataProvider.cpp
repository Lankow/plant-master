/*
*   DataProvider.cpp
*   ----------------------
*   Created on: 2023/09/29
*   Author: Lankow
*/
#include "DataProvider.hpp"

DataProvider::DataProvider(HumidityHandler *p_humidityHandler, NetworkHandler *p_networkHandler) {
    m_humidityHandler = p_humidityHandler;
    m_networkHandler = p_networkHandler;
}

int DataProvider::getHumidity() {
    return m_humidityHandler->getCurrentHumidity();
}

void DataProvider::setThreshold(int threshold) {
    return m_humidityHandler->setHumidityThreshold(threshold);
}