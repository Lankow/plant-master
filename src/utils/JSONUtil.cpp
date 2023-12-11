/*
 *   JSONUtil.cpp
 *   ----------------------
 *   Created on: 2023/10/20
 *   Author: Lankow
 */
#include <sstream>
#include <vector>
#include "utils/JSONUtil.hpp"

void JSONUtil::createSensorJson(const HumidityData &humidityData, JsonArray &humidityArray, const int sensorIndex)
{
    JsonObject sensorObject = humidityArray.createNestedObject();
    sensorObject["id"] = sensorIndex;
    sensorObject["lvl"] = humidityData.getCurrentHumidityLvl();
    sensorObject["threshold"] = humidityData.getHumidityThreshold();
    sensorObject["active"] = humidityData.getHumidityActive();
}

JsonArray JSONUtil::buildHumidityJson(const std::vector<HumidityData> &humidityData)
{
    DynamicJsonDocument doc(1024);
    JsonArray humidityArray = doc.createNestedArray();

    for (size_t i = 0; i < humidityData.size(); i++)
    {
        createSensorJson(humidityData[i], humidityArray, static_cast<int>(i));
    }
    return humidityArray;
}

std::string JSONUtil::serialize(const std::shared_ptr<DataProvider> &dataProvider)
{
    DynamicJsonDocument doc(1024);
    doc["room-humidity"] = dataProvider->getRoomHumidity();
    doc["temperature"] = dataProvider->getTemperature();
    doc["sensor"] = dataProvider->getSensorToWater();
    doc["humidity"] = buildHumidityJson(dataProvider->getHumidityData());

    std::ostringstream jsonOss;
    serializeJson(doc, jsonOss);
    return jsonOss.str();
}

void JSONUtil::handleData(std::shared_ptr<DataProvider> dataProvider, uint8_t *data, size_t len)
{
    StaticJsonDocument<BUFFER_SIZE> m_receivedJson;
    DeserializationError error = deserializeJson(m_receivedJson, (char *)data, len);

    if (error)
    {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.f_str());
        return;
    }

    const char *type = m_receivedJson["type"];

    if (strcmp(type, "edit") == 0)
    {
        uint8_t id = m_receivedJson["id"];

        if (m_receivedJson.containsKey("threshold"))
        {
            uint16_t threshold = m_receivedJson["threshold"];
            dataProvider->setHandlerThreshold(id, threshold);
        }

        if (m_receivedJson.containsKey("pin"))
        {
            uint8_t pin = m_receivedJson["pin"];
            // PIN handling To be Added
        }
    }
    else if (strcmp(type, "logs") == 0)
    {
        // Handle logs
        Serial.println("Handle Logs");
    }
}