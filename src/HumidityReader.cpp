/*
 *   HumidityReader.cpp
 *   ----------------------
 *   Created on: 2024/05/28
 *   Author: Lankow
 */
#include "HumidityReader.hpp"

HumidityReader::HumidityReader(const uint8_t pin):m_operatedPin(pin){};

void HumidityReader::readHumidity(){
    uint16_t humidity = analogRead(m_operatedPin);
    Serial.println(humidity);
}