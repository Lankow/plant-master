/*
 *   DHTReader.hpp
 *   ----------------------
 *   Created on: 2024/05/28
 *   Author: Lankow
 */
#ifndef DHT_READER_HPP
#define DHT_READER_HPP

#include <Arduino.h>
#include <DHT.h>
#include <memory>
#include "MQTTManager.hpp"
#include "Configurator.hpp"

class DHTReader
{
public:
    DHTReader(std::shared_ptr<Configurator> configurator, std::shared_ptr<MQTTManager> mqttManager);

    void init();
    void cyclic();

private:
    std::shared_ptr<MQTTManager> m_mqttManager;
    DHT m_dht;

    void readRoomTemperature();
    void readRoomHumidity();
};

#endif // DHT_READER_HPP