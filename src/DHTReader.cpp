/*
 *   DHTReader.cpp
 *   ----------------------
 *   Created on: 2024/05/28
 *   Author: Lankow
 */
#include "DHTReader.hpp"

DHTReader::DHTReader(const uint8_t pin, std::shared_ptr<MQTTManager> mqttManager)
    : m_dht(pin, DHT11),
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
    Serial.println("Temperature read error.");
  }
  else
  {
    m_mqttManager->publish(MQTT_ROOM_TEMPERATURE, std::to_string(temperature), 2, false);
  }
}

void DHTReader::readRoomHumidity()
{
  float humidity = m_dht.readHumidity();
  if (isnan(humidity))
  {
    m_mqttManager->publish(MQTT_ROOM_HUMIDITY, std::to_string(humidity), 2, false);
  }
  else
  {
    Serial.println(humidity);
  }
}