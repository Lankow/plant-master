/**
 * @file DHTReader.hpp
 * @date   2024-05-28
 * @author Lankow
 * @version 1.0
 *
 * @brief This file contains the definition of the DHTReader class.
 *
 * The DHTReader class is responsible for reading temperature and humidity data from a DHT sensor and
 * managing the communication with an MQTT server to publish the sensor data.
 */
#ifndef DHT_READER_HPP
#define DHT_READER_HPP

#include <Arduino.h>
#include <DHT.h>
#include <memory>
#include "network/MQTTManager.hpp"
#include "config/Configurator.hpp"

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