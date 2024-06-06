/*
 *   MQTTManager.hpp
 *   ----------------------
 *   Created on: 2024/06/04
 *   Author: Lankow
 */
#ifndef MQTT_MANAGER_HPP
#define MQTT_MANAGER_HPP

#include <Arduino.h>
#include <WiFi.h>
#include <AsyncMqttClient.h>
#include "Constants.hpp"
#include "sMQTTBroker.h"

#define PLANT_MASTER

class MQTTManager
{
public:
    MQTTManager();

    void init();
    void cyclic();
    void publish(const std::string &topic, const std::string &message, uint8_t qos, bool retain);

private:
    AsyncMqttClient m_client;
#ifdef PLANT_MASTER
    sMQTTBroker m_broker;
#endif

    void onMqttConnect(bool sessionPresent);
    void onMqttDisconnect(AsyncMqttClientDisconnectReason reason);
    void onMqttSubscribe(uint16_t packetId, uint8_t qos);
    void onMqttUnsubscribe(uint16_t packetId);
    void onMqttMessage(char *topic, char *payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total);
};

#endif // MQTT_MANAGER_HPP