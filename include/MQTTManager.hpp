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
#include <PubSubClient.h>
#include "Constants.hpp"
#include "sMQTTBroker.h"

#define PLANT_MASTER

class MQTTManager
{
public:
    MQTTManager();

    void init();
    void cyclic();

private:
    void connectMQTT();
    void callback(char *topic, byte *payload, unsigned int length);
    void publish(std::string topic, std::string message);
    void subscribe(std::string topic);

    WiFiClient m_espClient;
    PubSubClient m_client;
#ifdef PLANT_MASTER
    sMQTTBroker m_broker;
#endif
};

#endif // MQTT_MANAGER_HPP