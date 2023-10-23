/*
*   TemperatureHandler.cpp
*   ----------------------
*   Created on: 2023/10/05
*   Author: Lankow
*/
#include "handler/TemperatureHandler.hpp"
#include "Logger.hpp"

TemperatureHandler::TemperatureHandler(int pin) : m_dht(pin, DHT11) {
  m_dht.begin();
};

void TemperatureHandler::handleTemperature() {
  float t = m_dht.readTemperature();
  if (isnan(t)) {
      getLogger()->log(Logger::ERROR, "Temperature read error.");
  }
  else {
    getDataProvider()->setTemperature(t);
  }
}

void TemperatureHandler::handleRoomHumidity() {
  float t = m_dht.readHumidity();
  if (isnan(t)) {
      getLogger()->log(Logger::ERROR, "Room Humidity read error.");
  }
  else {
    getDataProvider()->setRoomHumidity(t);
  }
}

void TemperatureHandler::cyclic(){
  getLogger()->log(Logger::INFO, "TemperatureHandler - Cyclic Task");
  handleTemperature();
  handleRoomHumidity();
}