/*
 *   JSONHandler.cpp
 *   ----------------------
 *   Created on: 2023/10/20
 *   Author: Lankow
 */
#include <sstream>
#include <vector>
#include "handler/JSONHandler.hpp"
#include "TimeConverter.hpp"
#include <ArduinoJson.h>

JSONHandler::JSONHandler(std::shared_ptr<DataProvider> dataProvider) : m_dataProvider(dataProvider){};

const std::string JSONHandler::createSensorJson(const int sensorIndex)
{
    std::ostringstream jsonOss;
    const std::vector<HumidityData> humidityData = m_dataProvider->getHumidityData();

    jsonOss << "{\"id\":" << std::to_string(sensorIndex) << ",";
    jsonOss << "\"lvl\":" << std::to_string(humidityData[sensorIndex].getCurrentHumidityLvl()) << ",";
    jsonOss << "\"threshold\":" << std::to_string(humidityData[sensorIndex].getHumidityThreshold()) << ",";
    jsonOss << "\"active\":" << std::to_string(humidityData[sensorIndex].getHumidityActive()) << "}";

    return jsonOss.str();
}

const std::string JSONHandler::buildHumidityJson()
{
    std::ostringstream jsonOss;
    jsonOss << "{\"humidity\": [";
    const int numSensors = MAX_SENSORS_NO;

    for (int i = 0; i < numSensors; i++)
    {
        jsonOss << createSensorJson(i);
        if (i < numSensors - 1)
        {
            jsonOss << ",";
        }
    }

    jsonOss << "]}";

    return jsonOss.str();
}

const std::string JSONHandler::serialize(const JSONType jsonType)
{
    switch (jsonType)
    {
    case ROOM_HUMIDITY:
        return createJsonProperty("room-humidity", std::to_string(m_dataProvider->getRoomHumidity()));
    case TEMPERATURE:
        return createJsonProperty("temperature", std::to_string(m_dataProvider->getTemperature()));
    case SENSOR:
        return createJsonProperty("sensor", std::to_string(m_dataProvider->getSensorToWater()));
    case TIME:
        return createJsonProperty("time", TimeConverter::convertTime(TimeConverter::ConverstionType::JSON, m_dataProvider->getCurrentTime()));
    case HUMIDITY:
        return buildHumidityJson();
    default:
        return "{}";
    }
}

const std::string JSONHandler::createJsonProperty(const std::string &name, const std::string &value)
{
    return "{\"" + name + "\":" + value + "}";
}

void JSONHandler::handleData(uint8_t *data, size_t len)
{
    DeserializationError error = deserializeJson(m_receivedJson, (char *)data, len);
    if (error)
    {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.f_str());
        return;
    }

    if (!m_receivedJson.containsKey("id") || !m_receivedJson.containsKey("type"))
    {
        Serial.println(F("Missing required fields in JSON."));
        return;
    }

    uint8_t id = m_receivedJson["id"];

    if (strcmp(m_receivedJson["type"], "edit") == 0)
    {
        if (m_receivedJson.containsKey("threshold"))
        {
            uint16_t threshold = m_receivedJson["threshold"];
            m_dataProvider->setHandlerThreshold(id, threshold);
        }

        if (m_receivedJson.containsKey("pin"))
        {
            uint8_t pin = m_receivedJson["pin"];
            // PIN handling To be Added
        }
    }
}