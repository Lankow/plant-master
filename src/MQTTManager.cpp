/*
 *   MQTTManager.cpp
 *   ----------------------
 *   Created on: 2024/06/04
 *   Author: Lankow
 */
#include "MQTTManager.hpp"
#include "Constants.hpp"

MQTTManager::MQTTManager() : m_espClient(), m_client(m_espClient){};

void MQTTManager::init()
{
    if (WiFi.status() == WL_CONNECTED)
    {
        Serial.println("Initializing MQTT...");
        m_client.setServer(MQTT_SERVER_IP, MQTT_SERVER_PORT);
        m_client.setCallback([this](char *topic, uint8_t *payload, unsigned int length)
                             { this->callback(topic, payload, length); });
        connectMQTT();
    }
};

void MQTTManager::cyclic()
{
    if (!m_client.connected())
    {
        connectMQTT();
    }
};

void MQTTManager::connectMQTT()
{
    if (m_client.connect(MQTT_IDENTIFIER.c_str()))
    {
#ifdef PLANT_MASTER
        m_client.subscribe(MQTT_PLANT_HUMIDITY.c_str());
        m_client.subscribe(MQTT_ROOM_HUMIDITY.c_str());
        m_client.subscribe(MQTT_ROOM_TEMPERATURE.c_str());
#else
        m_client.subscribe(MQTT_PLANT_THRESHOLD.c_str());
#endif
    }
}

void MQTTManager::callback(char *topic, byte *payload, unsigned int length)
{
    Serial.println(topic);
    for (int i = 0; i < length; i++)
    {
        Serial.print((char)payload[i]);
    }
    Serial.println();
};

void MQTTManager::publish(std::string topic, std::string message)
{
    m_client.publish(topic.c_str(), message.c_str());
};

void MQTTManager::subscribe(std::string topic)
{
    m_client.subscribe(topic.c_str());
};
