/*
 *   DHTReader.cpp
 *   ----------------------
 *   Created on: 2024/05/28
 *   Author: Lankow
 */
#include "DHTReader.hpp"

DHTReader::DHTReader(std::shared_ptr<Configurator> configurator, std::shared_ptr<MQTTManager> mqttManager)
    : m_dht(configurator->getDhtPin(), DHT11),
      m_mqttManager(mqttManager){};

void DHTReader::init()
{
  m_dht.begin();
}

void DHTReader::cyclic()
{
  readRoomTemperature();
  readRoomHumidity();
}

void DHTReader::readRoomTemperature()
{
  float temperature = m_dht.readTemperature();
  if (isnan(temperature))
  {
    Serial.println("Room Temperature read error.");
  }
  else
  {
    Serial.println(temperature);
    m_mqttManager->publish(MQTT::ROOM_TEMPERATURE, std::to_string(temperature), 0, false);
  }
}

void DHTReader::readRoomHumidity()
{
  float humidity = m_dht.readHumidity();
  if (isnan(humidity))
  {
    Serial.println("Room humidity read error.");
  }
  else
  {
    Serial.println(humidity);
    m_mqttManager->publish(MQTT::ROOM_HUMIDITY, std::to_string(humidity), 0, false);
  }
}