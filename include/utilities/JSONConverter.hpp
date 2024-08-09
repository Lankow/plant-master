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

class JSONConverter
{
public:
    JSONConverter(std::shared_ptr<DataStorage> dataStorage);

    std::string serializeDataStorage() const;
    void handleWsEventData(uint8_t *data, size_t len);

private:
    std::shared_ptr<DataStorage> m_dataStorage;
    StaticJsonDocument<512> m_receivedJson;

    void serializePlantHumidityData(const PlantHumidityData &plantHumidityData, JsonArray &plantHumidityArray, int sensorIndex) const;
    JsonArray serializePlantsHumidity(const std::vector<PlantHumidityData> &plantHumidityData) const;
    uint16_t deserializeByKey(const std::string &keyName) const;
};

#endif // JSON_CONVERTER_HPP