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

JSONHandler::JSONHandler(std::shared_ptr<DataProvider> dataProvider) : m_dataProvider(dataProvider){};

void JSONHandler::createSensorJson(JsonArray &humidityArray, const int sensorIndex)
{
    const std::vector<HumidityData> humidityData = m_dataProvider->getHumidityData();

    JsonObject sensorObject = humidityArray.createNestedObject();
    sensorObject["id"] = sensorIndex;
    sensorObject["lvl"] = humidityData[sensorIndex].getCurrentHumidityLvl();
    sensorObject["threshold"] = humidityData[sensorIndex].getHumidityThreshold();
    sensorObject["active"] = humidityData[sensorIndex].getHumidityActive();
}

const JsonArray JSONHandler::buildHumidityJson()
{
    const int numSensors = MAX_SENSORS_NO;

    DynamicJsonDocument doc(1024);
    JsonArray humidityArray = doc.createNestedArray();

    for (int i = 0; i < numSensors; i++)
    {
        createSensorJson(humidityArray, i);
    }

    return humidityArray;
}

static const std::string JSONHandler::serialize()
{
    DynamicJsonDocument doc(1024);

    doc["room-humidity"] = m_dataProvider->getRoomHumidity();
    doc["temperature"] = m_dataProvider->getTemperature();
    doc["sensor"] = m_dataProvider->getSensorToWater();
    doc["time"] = TimeConverter::convertTime(TimeConverter::ConverstionType::JSON, m_dataProvider->getCurrentTime());
    doc["humidity"] = buildHumidityJson();

    std::ostringstream jsonOss;

    serializeJson(doc, jsonOss);

    return jsonOss.str();
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

    if (strcmp(m_receivedJson["type"], "edit") == 0)
    {
        uint8_t id = m_receivedJson["id"];

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
    else if (strcmp(m_receivedJson["type"], "logs") == 0)
    {
        // Handle logs
        Serial.println("Handle Logs");
    }
}