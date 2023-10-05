/*
*   TemperatureHandler.cpp
*   ----------------------
*   Created on: 2023/10/05
*   Author: Lankow
*/
#include "handler/TemperatureHandler.hpp"
#include "constants.hpp"

TemperatureHandler::TemperatureHandler(int pin) : m_dht(pin, DHT11) {
    // Constructor initialization list
};

void TemperatureHandler::readTemperature() {
  float t = m_dht.readTemperature();
  if (isnan(t)) {
    Serial.println("Temperature read error.");
  }
  else {
    Serial.println(t);
  }
}

void TemperatureHandler::readRoomHumidity() {
  float t = m_dht.readHumidity();
  if (isnan(t)) {
    Serial.println("Room Humidity read error.");
  }
  else {
    Serial.println(t);
  }
}