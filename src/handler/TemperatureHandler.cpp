/*
*   TemperatureHandler.cpp
*   ----------------------
*   Created on: 2023/10/05
*   Author: Lankow
*/
#include "handler/TemperatureHandler.hpp"

TemperatureHandler::TemperatureHandler(int pin) : m_dht(pin, DHT11) {
  m_dht.begin();
};

void TemperatureHandler::readTemperature() {
  float t = m_dht.readTemperature();
  if (isnan(t)) {
    Serial.println("Temperature read error.");
  }
  else {
    getDataProvider()->setTemperature(t);
  }
}

void TemperatureHandler::readRoomHumidity() {
  float t = m_dht.readHumidity();
  if (isnan(t)) {
    Serial.println("Room Humidity read error.");
  }
  else {
    getDataProvider()->setRoomHumidity(t);
  }
}

void TemperatureHandler::cyclic(){
  Serial.println("TemperatureHandler - Cyclic Task");
  readTemperature();
  readRoomHumidity();
}