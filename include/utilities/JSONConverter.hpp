/**
 * @file JSONConverter.hpp
 * @date   2024-05-31
 * @author Lankow
 * @version 1.0
 *
 * @brief This file contains the definition of the JSONConverter class.
 *
 * The JSONConverter class is responsible for serializing and deserializing data
 * to and from JSON format, specifically for handling data related to plant humidity
 * and device state.
 */
#ifndef JSON_CONVERTER_HPP
#define JSON_CONVERTER_HPP

#include <Arduino.h>
#include <ArduinoJson.h>
#include <memory>
#include "data/DataStorage.hpp"
#include "data/PlantHumidityData.hpp"

/**
 * @class JSONConverter
 * @brief A class for converting data to and from JSON format.
 *
 * The JSONConverter class handles the serialization and deserialization of plant humidity
 * data and device state, enabling the communication of this data over networks.
 */
class JSONConverter
{
public:
    /**
     * @brief Constructs a new JSONConverter object.
     *
     * @param dataStorage A shared pointer to a DataStorage object for accessing the data to be serialized/deserialized.
     */
    JSONConverter(std::shared_ptr<DataStorage> dataStorage);

    /**
     * @brief Serializes the data stored in DataStorage to a JSON string.
     *
     * This method serializes the data including room humidity, room temperature, water pump status,
     * active reader pin, and plants' humidity data into a JSON string.
     *
     * @return A JSON string representing the serialized data.
     */
    std::string serializeDataStorage() const;

    /**
     * @brief Handles WebSocket event data by deserializing it from JSON format.
     *
     * This method deserializes the received JSON data and updates the humidity threshold
     * for a specified sensor based on the provided data.
     *
     * @param data The JSON data received via WebSocket.
     * @param len The length of the received data.
     */
    void handleWsEventData(uint8_t *data, size_t len);

private:
    std::shared_ptr<DataStorage> m_dataStorage; /**< Shared pointer to the DataStorage object. */
    StaticJsonDocument<512> m_receivedJson;     /**< JSON document for holding received data. */

    /**
     * @brief Serializes the humidity data for multiple plants into a JSON array.
     *
     * @param plantHumidityData A vector of PlantHumidityData objects representing the humidity data for each plant.
     * @param doc The JSON document to which the humidity data should be added.
     * @return A JSON array representing the serialized plant humidity data.
     */
    JsonArray serializePlantsHumidity(const std::vector<PlantHumidityData> &plantHumidityData, DynamicJsonDocument &doc) const;

    /**
     * @brief Serializes the humidity data for a single plant and adds it to a JSON array.
     *
     * @param plantHumidityData A PlantHumidityData object representing the humidity data for a single plant.
     * @param plantHumidityArray The JSON array to which the serialized data should be added.
     * @param sensorIndex The index of the sensor to be used in the JSON object.
     */
    void serializePlantHumidityData(const PlantHumidityData &plantHumidityData, JsonArray &plantHumidityArray, int sensorIndex) const;

    /**
     * @brief Deserializes an integer value from the JSON document by key name.
     *
     * This method retrieves an integer value associated with the specified key from the received JSON document.
     *
     * @param keyName The name of the key whose value should be deserialized.
     * @return The deserialized integer value.
     */
    uint16_t deserializeByKey(const std::string &keyName) const;
};

#endif // JSON_CONVERTER_HPP