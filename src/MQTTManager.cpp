/*
 *   MQTTManager.cpp
 *   ----------------------
 *   Created on: 2024/06/04
 *   Author: Lankow
 */
#include "MQTTManager.hpp"
#include "Constants.hpp"

// Constructor definition
#ifdef PLANT_MASTER
MQTTManager::MQTTManager(std::shared_ptr<DataHandler> dataHandler, std::shared_ptr<Configurator> configurator)
    : m_dataHandler(dataHandler),
      m_configurator(configurator),
      m_broker(),
      m_client() {}
#else
MQTTManager::MQTTManager(std::shared_ptr<DataHandler> dataHandler)
    : m_dataHandler(dataHandler),
      m_client(){};
#endif

// Method to initialize the MQTTManager
void MQTTManager::init()
{
    if (WiFi.status() == WL_CONNECTED)
    {
#ifdef PLANT_MASTER
        Serial.println("Initializing MQTT Broker...");
        m_broker.init(MQTT_SERVER_PORT);
#endif
        Serial.println("Initializing MQTT...");

        // Using lambda functions for MQTT callbacks
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

        m_client.setServer(MQTT_SERVER_IP, MQTT_SERVER_PORT);
    }
}

// Method to cyclically check and manage MQTT connections and messages
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

// Method called when MQTT connects
void MQTTManager::onMqttConnect(bool sessionPresent)
{
    Serial.println("Connected to MQTT.");
#ifdef PLANT_MASTER
    m_client.subscribe(MQTT_ROOM_HUMIDITY.c_str(), 2);
    m_client.subscribe(MQTT_ROOM_TEMPERATURE.c_str(), 2);
    for (int pin : m_configurator->getReaderPins())
    {
        std::string topic = MQTT_PLANT_HUMIDITY + "/" + std::to_string(pin);
        m_client.subscribe(topic.c_str(), 2);
    }
#else
    m_client.subscribe(MQTT_WATER_ACTIVE.c_str(), 2);
    m_client.subscribe(MQTT_WATER_PIN.c_str(), 2);
#endif
}

// Method called when MQTT disconnects
void MQTTManager::onMqttDisconnect(AsyncMqttClientDisconnectReason reason)
{
    Serial.println("Disconnected from MQTT.");
    Serial.print("Reason: ");
    Serial.println(static_cast<int>(reason)); // Print the reason code
}
// Method called when MQTT subscription is acknowledged
void MQTTManager::onMqttSubscribe(uint16_t packetId, uint8_t qos)
{
    Serial.println("Subscribe acknowledged.");
}

// Method called when MQTT unsubscription is acknowledged
void MQTTManager::onMqttUnsubscribe(uint16_t packetId)
{
    Serial.println("Unsubscribe acknowledged.");
}

// Method called when an MQTT message is received
void MQTTManager::onMqttMessage(char *topic, char *payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total)
{
    std::string strTopic(topic);
    std::string strPayload(payload, len);

    m_dataHandler->handleData(strTopic, strPayload);
}

// Method to publish a message to a specific MQTT topic
void MQTTManager::publish(const std::string &topic, const std::string &message, uint8_t qos, bool retain)
{
    if (m_client.connected())
    {
        m_client.publish(topic.c_str(), qos, retain, message.c_str());
        Serial.println("Message published:");
        Serial.print("  topic: ");
        Serial.println(topic.c_str());
        Serial.print("  message: ");
        Serial.println(message.c_str());
    }
    else
    {
        Serial.println("Failed to publish message. MQTT client is not connected.");
    }
}