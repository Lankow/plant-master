/**
 * @file DHTReader.cpp
 * @date   2024-05-28
 * @author Lankow
 * @version 1.0
 *
 * @brief This file contains the implementation of the DHTReader class.
 *
 * The DHTReader class is responsible for reading temperature and humidity data from a DHT sensor and
 * managing the communication with an MQTT server to publish the sensor data.
 */

#include "core/DHTReader.hpp"

DHTReader::DHTReader(std::shared_ptr<Configurator> configurator, std::shared_ptr<MQTTManager> mqttManager)
    : m_dht(configurator->getDhtPin(), DHT11),
      m_mqttManager(mqttManager) {}

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
    Serial.println("Error: Failed to read room temperature.");
  }
  else
  {
    Serial.print("Room Temperature: ");
    Serial.println(temperature);
    m_mqttManager->publish(MQTT::ROOM_TEMPERATURE, std::to_string(temperature), 0, false);
  }
}

void DHTReader::readRoomHumidity()
{
  float humidity = m_dht.readHumidity();
  if (isnan(humidity))
  {
    Serial.println("Error: Failed to read room humidity.");
  }
  else
  {
    Serial.print("Room Humidity: ");
    Serial.println(humidity);
    m_mqttManager->publish(MQTT::ROOM_HUMIDITY, std::to_string(humidity), 0, false);
  }
}
