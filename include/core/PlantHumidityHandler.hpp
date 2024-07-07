/**
 * @file PlantHumidityHandler.hpp
 * @date   2024-05-28
 * @author Lankow
 * @version 1.0
 *
 * @brief This file contains the definition of the PlantHumidityHandler class.
 *
 * The PlantHumidityHandler class is responsible for reading humidity data from plant sensors and
 * managing the operation of valves based on the humidity readings and configuration settings.
 */
#ifndef PLANT_HUMIDITY_HANDLER_HPP
#define PLANT_HUMIDITY_HANDLER_HPP

#include <Arduino.h>
#include <memory>
#include "network/MQTTManager.hpp"
#include "config/Configurator.hpp"
#include "data/DataStorage.hpp"

/**
 * @class PlantHumidityHandler
 * @brief A class for handling plant humidity readings and controlling irrigation valves.
 *
 * The PlantHumidityHandler class reads humidity data from sensors, publishes it via MQTT, and
 * controls irrigation valves based on configuration settings and data storage state.
 */
class PlantHumidityHandler
{
public:
    /**
     * @brief Constructs a new PlantHumidityHandler object.
     *
     * @param configurator A shared pointer to a Configurator object for configuration settings.
     * @param mqttManager A shared pointer to an MQTTManager object for managing MQTT communication.
     * @param dataStorage A shared pointer to a DataStorage object for storing data and state.
     */
    PlantHumidityHandler(std::shared_ptr<Configurator> configurator, std::shared_ptr<MQTTManager> mqttManager, std::shared_ptr<DataStorage> dataStorage);

    /**
     * @brief Periodically reads humidity data and controls valves.
     *
     * This method should be called cyclically to ensure that humidity data is read and valves
     * are controlled at regular intervals.
     */
    void cyclic();

private:
    std::shared_ptr<MQTTManager> m_mqttManager;   /**< A shared pointer to an MQTTManager object for managing MQTT communication. */
    std::shared_ptr<Configurator> m_configurator; /**< A shared pointer to a Configurator object for configuration settings. */
    std::shared_ptr<DataStorage> m_dataStorage;   /**< A shared pointer to a DataStorage object for storing data and state. */

    /**
     * @brief Reads the current humidity from the sensors.
     *
     * This method reads humidity data from the configured sensor pins and publishes it via MQTT.
     */
    void readHumidity();

    /**
     * @brief Opens the irrigation valve associated with the specified reader pin.
     *
     * @param readerPin The pin associated with the sensor whose valve should be opened.
     */
    void openValve(uint16_t readerPin);

    /**
     * @brief Closes all irrigation valves.
     *
     * This method closes all irrigation valves.
     */
    void closeValves();
};

#endif // PLANT_HUMIDITY_HANDLER_HPP