/*
 *   JSONConverter.cpp
 *   ----------------------
 *   Created on: 2024/05/31
 *   Author: Lankow
 */
#include "JSONConverter.hpp"
#include <sstream>

JSONConverter::JSONConverter(std::shared_ptr<DataStorage> dataStorage) : m_dataStorage(dataStorage){};

std::string JSONConverter::serializeDataStorage()
{
    DynamicJsonDocument doc(1024);
    doc["room-humidity"] = m_dataStorage->getRoomHumidity();
    doc["room-temperature"] = m_dataStorage->getRoomTemperature();
    doc["plants-humidity"] = serializePlantsHumidity(m_dataStorage->getPlantsHumidityData());

    std::ostringstream jsonOss;
    serializeJson(doc, jsonOss);
    return jsonOss.str();
};

JsonArray JSONConverter::serializePlantsHumidity(const std::vector<PlantHumidityData> &planthumidityData)
{
    DynamicJsonDocument doc(1024);
    JsonArray plantHumidityArray = doc.createNestedArray();

    for (size_t i = 0; i < planthumidityData.size(); i++)
    {
        serializePlantHumidityData(planthumidityData[i], plantHumidityArray, static_cast<int>(i));
    }
    return plantHumidityArray;
}

void JSONConverter::serializePlantHumidityData(const PlantHumidityData &plantHumidityData, JsonArray &plantHumidityArray, const int sensorIndex)
{
    JsonObject sensorObject = plantHumidityArray.createNestedObject();
    sensorObject["id"] = sensorIndex;
    sensorObject["humidity"] = plantHumidityData.getCurrentHumidity();
    sensorObject["threshold"] = plantHumidityData.getHumidityThreshold();
}
