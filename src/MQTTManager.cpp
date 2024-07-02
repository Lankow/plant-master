/*
 *   MQTTManager.cpp
 *   ----------------------
 *   Created on: 2024/06/04
 *   Author: Lankow
 */
#include "MQTTManager.hpp"

#ifdef PLANT_MASTER
MQTTManager::MQTTManager(std::shared_ptr<DataHandler> dataHandler, std::shared_ptr<Configurator> configurator)
    : m_dataHandler(std::move(dataHandler)),
      m_configurator(std::move(configurator)),
      m_broker(),
      m_client() {}
#else
MQTTManager::MQTTManager(std::shared_ptr<DataHandler> dataHandler)
    : m_dataHandler(std::move(dataHandler)),
      m_client() {}
#endif

void MQTTManager::init()
{
    if (WiFi.status() == WL_CONNECTED)
    {
#ifdef PLANT_MASTER
        Serial.println("Initializing MQTT Broker...");
        m_broker.init(Network::Ports::MQTT_SERVER);
#endif
        Serial.println("Initializing MQTT...");

        m_client.onConnect([this](bool sessionPresent)
                           { this->onMqttConnect(sessionPresent); });
        m_client.onDisconnect([this](AsyncMqttClientDisconnectReason reason)
                              { this->onMqttDisconnect(reason); });
        m_client.onSubscribe([this](uint16_t packetId, uint8_t qos)
                             { this->onMqttSubscribe(packetId, qos); });
        m_client.onUnsubscribe([this](uint16_t packetId)
                               { this->onMqttUnsubscribe(packetId); });
        m_client.onMessage([this](char *topic, char *payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total)
                           { this->onMqttMessage(topic, payload, properties, len, index, total); });

        m_client.setServer(Network::IP::MQTT_SERVER, Network::Ports::MQTT_SERVER);
        m_client.connect();
    }
    else
    {
        Serial.println("WiFi not connected.");
    }
}

void MQTTManager::cyclic()
{
#ifdef PLANT_MASTER
    m_broker.update();
#endif
    if (!m_client.connected())
    {
        Serial.println("Not Connected");
        m_client.connect();
    }
}

void MQTTManager::onMqttConnect(bool sessionPresent)
{
    Serial.println("Connected to MQTT.");
#ifdef PLANT_MASTER
    m_client.subscribe(MQTT::ROOM_HUMIDITY.c_str(), 2);
    m_client.subscribe(MQTT::ROOM_TEMPERATURE.c_str(), 2);
    for (const int pin : m_configurator->getReaderPins())
    {
        std::string topic = MQTT::PLANT_HUMIDITY + "/" + std::to_string(pin);
        m_client.subscribe(topic.c_str(), 2);
    }
#else
    m_client.subscribe(MQTT::WATER_ACTIVE.c_str(), 2);
    m_client.subscribe(MQTT::WATER_PIN.c_str(), 2);
#endif
}

void MQTTManager::onMqttDisconnect(AsyncMqttClientDisconnectReason reason)
{
    Serial.println("Disconnected from MQTT.");
    Serial.print("Reason: ");
    Serial.println(static_cast<int>(reason)); // Print the reason code
}

void MQTTManager::onMqttSubscribe(uint16_t packetId, uint8_t qos)
{
    Serial.println("Subscribe acknowledged.");
    Serial.print("Packet ID: ");
    Serial.println(packetId);
    Serial.print("QoS: ");
    Serial.println(qos);
}

void MQTTManager::onMqttUnsubscribe(uint16_t packetId)
{
    Serial.println("Unsubscribe acknowledged.");
    Serial.print("Packet ID: ");
    Serial.println(packetId);
}

void MQTTManager::onMqttMessage(char *topic, char *payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total)
{
    std::string strTopic(topic);
    std::string strPayload(payload, len);

    m_dataHandler->handleData(strTopic, strPayload);
}

void MQTTManager::publish(const std::string &topic, const std::string &message, uint8_t qos, bool retain)
{
    if (m_client.connected())
    {
        m_client.publish(topic.c_str(), qos, retain, message.c_str());
        Serial.println("Message published:");
        Serial.print("  Topic: ");
        Serial.println(topic.c_str());
        Serial.print("  Message: ");
        Serial.println(message.c_str());
    }
    else
    {
        Serial.println("Failed to publish message. MQTT client is not connected.");
    }
}
