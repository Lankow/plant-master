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

private:
    std::shared_ptr<DataStorage> m_dataStorage;
    static JsonArray serializePlantsHumidity(const std::vector<PlantHumidityData> &planthumidityData);
    static void serializePlantHumidityData(const PlantHumidityData &plantHumidityData, JsonArray &plantHumidityArray, const int sensorIndex);
};

#endif // JSON_CONVERTER_HPP