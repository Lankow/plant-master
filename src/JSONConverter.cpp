/*
 *   JSONConverter.cpp
 *   ----------------------
 *   Created on: 2024/05/31
 *   Author: Lankow
 */
#include "JSONConverter.hpp"
#include <sstream>

JSONConverter::JSONConverter(std::shared_ptr<DataStorage> dataStorage) : m_dataStorage(dataStorage){};

#ifdef PLANT_MASTER
std::string JSONConverter::serializeDataStorage()
{
    DynamicJsonDocument doc(1024);
    doc["roomHumidity"] = m_dataStorage->getRoomHumidity();
    doc["roomTemperature"] = m_dataStorage->getRoomTemperature();
    doc["waterPumpActive"] = m_dataStorage->getIsWaterPumpActive();
    doc["activeReaderPin"] = m_dataStorage->getActiveReaderPin();
    doc["plantsHumidity"] = serializePlantsHumidity(m_dataStorage->getPlantsHumidityData());

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
    sensorObject["pin"] = plantHumidityData.getAssignedPin();
    sensorObject["humidity"] = plantHumidityData.getCurrentHumidity();
    sensorObject["threshold"] = plantHumidityData.getHumidityThreshold();
}

void JSONConverter::handleWsEventData(uint8_t *data, size_t len)
{
    DeserializationError error = deserializeJson(m_receivedJson, (char *)data, len);

    if (error)
    {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.f_str());
        return;
    }

    uint16_t threshold = deserializeByKey(data, len, "threshold");
    uint8_t pin = deserializeByKey(data, len, "pin");
    m_dataStorage->setHumidityThreshold(pin, threshold);
}

uint16_t JSONConverter::deserializeByKey(uint8_t *data, size_t len, const std::string &keyName)
{
    if (m_receivedJson.containsKey(keyName))
    {
        if (m_receivedJson[keyName].is<uint16_t>())
        {
            return m_receivedJson[keyName].as<uint16_t>();
        }
        else if (m_receivedJson[keyName].is<uint8_t>())
        {
            return m_receivedJson[keyName].as<uint8_t>();
        }
        else
        {
            Serial.println(F("Unexpected data type for the specified key."));
            return 0;
        }
    }
    else
    {
        Serial.println(F("Key not found in JSON."));
        return 0;
    }
}
#endif