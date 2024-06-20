/*
 *   JSONConverter.hpp
 *   ----------------------
 *   Created on: 2024/05/31
 *   Author: Lankow
 */
#ifndef JSON_CONVERTER_HPP
#define JSON_CONVERTER_HPP

#include <Arduino.h>
#include <ArduinoJson.h>
#include <memory>
#include "DataStorage.hpp"
#include "PlantHumidityData.hpp"

class JSONConverter
{
public:
    JSONConverter(std::shared_ptr<DataStorage> dataStorage);

    std::string serializeDataStorage();
    void handleWsEventData(uint8_t *data, size_t len);

private:
    std::shared_ptr<DataStorage> m_dataStorage;
    StaticJsonDocument<512> m_receivedJson;

    JsonArray serializePlantsHumidity(const std::vector<PlantHumidityData> &planthumidityData);
    void serializePlantHumidityData(const PlantHumidityData &plantHumidityData, JsonArray &plantHumidityArray, const int sensorIndex);
    uint16_t deserializeByKey(uint8_t *data, size_t len, const std::string &keyName);
};

#endif // JSON_CONVERTER_HPP