/*
 *   DHTReader.cpp
 *   ----------------------
 *   Created on: 2024/05/28
 *   Author: Lankow
 */
#include "DHTReader.hpp"

DHTReader::DHTReader(const uint8_t pin) : m_dht(pin, DHT11)
{
  m_dht.begin();
};

void DHTReader::readRoomTemperature()
{
  float temperature = m_dht.readTemperature();
  if (isnan(temperature))
  {
    Serial.println("Temperature read error.");
  }
  else
  {
    Serial.println(temperature);
  }
}

void DHTReader::readRoomHumidity()
{
  float humidity = m_dht.readHumidity();
  if (isnan(humidity))
  {
    Serial.println("Room Humidity read error.");
  }
  else
  {
    Serial.println(humidity);
  }
}