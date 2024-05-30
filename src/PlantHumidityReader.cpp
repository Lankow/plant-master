/*
 *   PlantHumidityReader.cpp
 *   ----------------------
 *   Created on: 2024/05/28
 *   Author: Lankow
 */
#include "PlantHumidityReader.hpp"

PlantHumidityReader::PlantHumidityReader(const uint8_t pin):m_operatedPin(pin){};

void PlantHumidityReader::readHumidity(){
    uint16_t humidity = analogRead(m_operatedPin);
    Serial.println(humidity);
}