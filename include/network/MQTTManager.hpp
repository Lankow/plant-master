/**
 * @file MQTTManager.hpp
 * @date   2024-06-04
 * @author Lankow
 * @version 1.0
 *
 * @brief This file contains the definition of the MQTTManager class.
 *
 * The MQTTManager class is responsible for managing MQTT communication for the device,
 * including initializing connections, handling messages, and maintaining the connection state.
 */
#ifndef MQTT_MANAGER_HPP
#define MQTT_MANAGER_HPP

#include <Arduino.h>
#include <WiFi.h>
#include <AsyncMqttClient.h>
#include "sMQTTBroker.h"
#include "config/Constants.hpp"
#include "config/Configurator.hpp"
#include "data/DataHandler.hpp"

/**
 * @class MQTTManager
 * @brief Manages MQTT communication for the device.
 */
class MQTTManager
{
public:
    /**
     * @brief Constructs a new MQTTManager object with a data handler and configurator.
     * @param dataHandler A shared pointer to a DataHandler object for handling data.
     * @param configurator A shared pointer to a Configurator object for configuration settings.
     */
    MQTTManager(std::shared_ptr<DataHandler> dataHandler, std::shared_ptr<Configurator> configurator);

    /**
     * @brief Constructs a new MQTTManager object with only a data handler.
     * @param dataHandler A shared pointer to a DataHandler object for handling data.
     */
    MQTTManager(std::shared_ptr<DataHandler> dataHandler);

    /**
     * @brief Initializes the MQTTManager, setting up MQTT connections and callbacks.
     */
    void init();

    /**
     * @brief Periodically checks and maintains the MQTT connection.
     */
    void cyclic();

    /**
     * @brief Publishes a message to a specified MQTT topic.
     * @param topic The topic to publish to.
     * @param message The message to publish.
     * @param qos The Quality of Service level for the message.
     * @param retain Whether the message should be retained.
     */
    void publish(const std::string &topic, const std::string &message, uint8_t qos, bool retain);

private:
    std::shared_ptr<DataHandler> m_dataHandler;   /**< Shared pointer to a DataHandler object. */
    std::shared_ptr<Configurator> m_configurator; /**< Shared pointer to a Configurator object. */
    AsyncMqttClient m_client;                     /**< MQTT client for handling MQTT communication. */

#ifdef PLANT_MASTER
    sMQTTBroker m_broker; /**< MQTT broker for the plant master. */
#endif

    /**
     * @brief Callback function called when the MQTT client connects to the broker.
     * @param sessionPresent Whether a session is present.
     */
    void onMqttConnect(bool sessionPresent);

    /**
     * @brief Callback function called when the MQTT client disconnects from the broker.
     * @param reason The reason for the disconnection.
     */
    void onMqttDisconnect(AsyncMqttClientDisconnectReason reason);

    /**
     * @brief Callback function called when the MQTT client subscribes to a topic.
     * @param packetId The packet ID of the subscription.
     * @param qos The Quality of Service level.
     */
    void onMqttSubscribe(uint16_t packetId, uint8_t qos);

    /**
     * @brief Callback function called when the MQTT client unsubscribes from a topic.
     * @param packetId The packet ID of the unsubscription.
     */
    void onMqttUnsubscribe(uint16_t packetId);

    /**
     * @brief Callback function called when an MQTT message is received.
     * @param topic The topic of the message.
     * @param payload The payload of the message.
     * @param properties The properties of the message.
     * @param len The length of the payload.
     * @param index The index of the payload.
     * @param total The total length of the payload.
     */
    void onMqttMessage(char *topic, char *payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total);
};

#endif // MQTT_MANAGER_HPP