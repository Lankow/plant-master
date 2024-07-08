/**
 * @file JSONConverter.cpp
 * @date   2024-05-31
 * @author Lankow
 * @version 1.0
 *
 * @brief This file contains the implementation of the JSONConverter class.
 *
 * The JSONConverter class is responsible for serializing and deserializing data
 * to and from JSON format, specifically for handling data related to plant humidity
 * and device state.
 */
#include "utilities/JSONConverter.hpp"
#include <sstream>

JSONConverter::JSONConverter(std::shared_ptr<DataStorage> dataStorage)
    : m_dataStorage(dataStorage) {}

#ifdef PLANT_MASTER
std::string JSONConverter::serializeDataStorage() const
{
    DynamicJsonDocument doc(1024);
    doc["roomHumidity"] = m_dataStorage->getRoomHumidity();
    doc["roomTemperature"] = m_dataStorage->getRoomTemperature();
    doc["waterPumpActive"] = m_dataStorage->isWaterPumpActive();
    doc["activeReaderPin"] = m_dataStorage->getActiveReaderPin();
    doc["plantsHumidity"] = serializePlantsHumidity(m_dataStorage->getPlantsHumidityData(), doc);

    std::ostringstream jsonOss;
    serializeJson(doc, jsonOss);
    return jsonOss.str();
}

JsonArray JSONConverter::serializePlantsHumidity(const std::vector<PlantHumidityData> &plantHumidityData, DynamicJsonDocument &doc) const
{
    JsonArray plantHumidityArray = doc.createNestedArray();

    for (size_t i = 0; i < plantHumidityData.size(); ++i)
    {
        serializePlantHumidityData(plantHumidityData[i], plantHumidityArray, static_cast<int>(i));
    }
    return plantHumidityArray;
}

void JSONConverter::serializePlantHumidityData(const PlantHumidityData &plantHumidityData, JsonArray &plantHumidityArray, int sensorIndex) const
{
    JsonObject sensorObject = plantHumidityArray.createNestedObject();
    sensorObject["id"] = sensorIndex;
    sensorObject["pin"] = plantHumidityData.getAssignedPin();
    sensorObject["humidity"] = plantHumidityData.getCurrentHumidity();
    sensorObject["threshold"] = plantHumidityData.getHumidityThreshold();
}

void JSONConverter::handleWsEventData(uint8_t *data, size_t len)
{
    DeserializationError error = deserializeJson(m_receivedJson, data, len);

    if (error)
    {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.f_str());
        return;
    }

    uint16_t threshold = deserializeByKey("threshold");
    uint8_t pin = static_cast<uint8_t>(deserializeByKey("pin"));
    m_dataStorage->setHumidityThreshold(pin, threshold);
}

uint16_t JSONConverter::deserializeByKey(const std::string &keyName) const
{
    if (m_receivedJson.containsKey(keyName))
    {
        return m_receivedJson[keyName].as<uint16_t>();
    }
    else
    {
        Serial.print(F("Key not found in JSON: "));
        Serial.println(keyName.c_str());
        return 0;
    }
}
#endif