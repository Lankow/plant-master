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
    /**
     * @brief Constructs a new DHTReader object.
     *
     * @param configurator A shared pointer to a Configurator object for configuration settings.
     * @param mqttManager A shared pointer to an MQTTManager object for managing MQTT communication.
     */
    DHTReader(std::shared_ptr<Configurator> configurator, std::shared_ptr<MQTTManager> mqttManager);

    /**
     * @brief Initializes the DHT sensor.
     *
     * This method initializes the DHT sensor to prepare it for reading data.
     */
    void init();

    /**
     * @brief Periodically reads data from the DHT sensor and publishes it via MQTT.
     *
     * This method should be called cyclically to ensure that temperature and humidity data are read
     * and published at regular intervals.
     */
    void cyclic();

private:
    std::shared_ptr<MQTTManager> m_mqttManager; /**< A shared pointer to an MQTTManager object for managing MQTT communication. */
    DHT m_dht;                                  /**< An instance of the DHT sensor. */

    /**
     * @brief Reads the current room temperature from the DHT sensor.
     *
     * This method reads the temperature data from the DHT sensor, processes it, and publishes it via MQTT.
     * If the reading fails, an error message is printed to the Serial monitor.
     */
    void readRoomTemperature();

    /**
     * @brief Reads the current room humidity from the DHT sensor.
     *
     * This method reads the humidity data from the DHT sensor, processes it, and publishes it via MQTT.
     * If the reading fails, an error message is printed to the Serial monitor.
     */
    void readRoomHumidity();
};

#endif // DHT_READER_HPP