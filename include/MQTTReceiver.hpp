/*
 *   MQTTReceiver.hpp
 *   ----------------------
 *   Created on: 2024/06/04
 *   Author: Lankow
 */
#ifndef MQTT_RECEIVER_HPP
#define MQTT_RECEIVER_HPP

#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

class MQTTReceiver
{
public:
    MQTTReceiver();

    void init();
    void cyclic();

private:
};

#endif // MQTT_RECEIVER_HPP