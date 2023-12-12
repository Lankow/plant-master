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

WebSocketEvtType JSONUtil::getEventType(std::shared_ptr<DataProvider> dataProvider, uint8_t *data, size_t len)
{
    StaticJsonDocument<BUFFER_SIZE> m_receivedJson;
    DeserializationError error = deserializeJson(m_receivedJson, (char *)data, len);

    if (error)
    {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.f_str());
        return WebSocketEvtType::UNKNOWN;
    }

    const char *type = m_receivedJson["type"];

    if (strcmp(type, "edit") == 0)
    {
        return WebSocketEvtType::SET_THRESHOLD;
    }
    else if (strcmp(type, "logs") == 0)
    {
        return WebSocketEvtType::GET_LOGS;
    }
    else
    {
        return WebSocketEvtType::UNKNOWN;
    }
}

std::string JSONUtil::toJSONString(const std::vector<std::string> &logsList)
{
    DynamicJsonDocument doc(1024);
    JsonObject logsObject = doc.createNestedObject("logs");
    JsonArray logsArray = logsObject.createNestedArray("files");

    for (const auto &log : logsList)
    {
        logsArray.add(log);
    }

    std::string logsJson;
    serializeJson(doc, logsJson);

    return logsJson;
}

uint16_t JSONUtil::deserializeByKey(uint8_t *data, size_t len, const std::string &keyName)
{
    StaticJsonDocument<BUFFER_SIZE> m_receivedJson;
    DeserializationError error = deserializeJson(m_receivedJson, (char *)data, len);

    if (error)
    {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.f_str());
        return 0;
    }

    if (m_receivedJson.containsKey(keyName))
    {
        return m_receivedJson[keyName];
    }
    else
    {
        return 0;
    }
}