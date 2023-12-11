/*
 *   TemperatureHandler.cpp
 *   ----------------------
 *   Created on: 2023/10/05
 *   Author: Lankow
 */
#include "handler/TemperatureHandler.hpp"
#include "utils/Logger.hpp"

TemperatureHandler::TemperatureHandler(const uint8_t pin) : m_dht(pin, DHT11)
{
  m_dht.begin();
};

void TemperatureHandler::handleTemperature()
{
  float t = m_dht.readTemperature();
  if (isnan(t))
  {
    Logger::log(Logger::ERROR, "Temperature read error.");
  }
  else
  {
    m_dataProvider->setTemperature(t);
  }
}

void TemperatureHandler::handleRoomHumidity()
{
  float t = m_dht.readHumidity();
  if (isnan(t))
  {
    Logger::log(Logger::ERROR, "Room Humidity read error.");
  }
  else
  {
    m_dataProvider->setRoomHumidity(t);
  }
}

void TemperatureHandler::init()
{
  Logger::log(Logger::INFO, "TemperatureHandler - Init");
}

void TemperatureHandler::cyclic()
{
  Logger::log(Logger::INFO, "TemperatureHandler - Cyclic Task");
  handleTemperature();
  handleRoomHumidity();
}