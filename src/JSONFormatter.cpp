/*
 *   JSONFormatter.cpp
 *   ----------------------
 *   Created on: 2023/10/20
 *   Author: Lankow
 */
#include <sstream>
#include <vector>
#include "JSONFormatter.hpp"
#include "TimeConverter.hpp"

JSONFormatter::JSONHandler(std::shared_ptr<const DataProvider> dataProvider) : m_dataProvider(dataProvider){};

const std::string JSONFormatter::createSensorJson(const int sensorIndex)
{
    std::ostringstream jsonOss;
    const std::vector<HumidityData> humidityData = m_dataProvider->getHumidityData();

    jsonOss << "{\"id\":" << std::to_string(sensorIndex) << ",";
    jsonOss << "\"lvl\":" << std::to_string(humidityData[sensorIndex].getCurrentHumidityLvl()) << ",";
    jsonOss << "\"threshold\":" << std::to_string(humidityData[sensorIndex].getHumidityThreshold()) << ",";
    jsonOss << "\"active\":" << std::to_string(humidityData[sensorIndex].getHumidityActive()) << "}";

    return jsonOss.str();
}

const std::string JSONFormatter::buildHumidityJson()
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

const std::string JSONFormatter::serialize(const JSONType jsonType)
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

const std::string JSONFormatter::createJsonProperty(const std::string &name, const std::string &value)
{
    return "{\"" + name + "\":" + value + "}";
}