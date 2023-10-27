/*
 *   JSONFormatter.cpp
 *   ----------------------
 *   Created on: 2023/10/20
 *   Author: Lankow
 */
#include "JSONFormatter.hpp"

JSONFormatter::JSONFormatter(DataProvider *p_dataProvider) : m_dataProvider(p_dataProvider){};

String JSONFormatter::createSensorJson(int sensorIndex)
{
    String sensorJson = "{\"lvl\":" + String(m_dataProvider->getCurrentHumidityLvl()[sensorIndex]) + ",";
    sensorJson += "\"threshold\":" + String(m_dataProvider->getHumidityThreshold()[sensorIndex]) + ",";
    sensorJson += "\"active\":" + String(m_dataProvider->getHumidityActive()[sensorIndex]) + "}";

    return sensorJson;
}

String JSONFormatter::buildHumidityJson()
{
    String jsonStr = "{\"humidity\": [";
    const int numSensors = MAX_SENSORS_NO;

    for (int i = 0; i < numSensors; i++)
    {
        jsonStr += createSensorJson(i);
        if (i < numSensors - 1)
        {
            jsonStr += ",";
        }
    }

    jsonStr += "]}";

    return jsonStr;
}

String JSONFormatter::serialize(JSONType p_jsonType)
{
    switch (p_jsonType)
    {
    case ROOM_HUMIDITY:
        return createJsonProperty("room-humidity", String(m_dataProvider->getRoomHumidity()));
    case TEMPERATURE:
        return createJsonProperty("temperature", String(m_dataProvider->getTemperature()));
    case SENSOR:
        return createJsonProperty("sensor", String(m_dataProvider->getSensorToWater()));
    case TIME:
        return createJsonProperty("time", m_dataProvider->getCurrentTime());
    case HUMIDITY:
        return buildHumidityJson();
    default:
        return "{}";
    }
}

String JSONFormatter::createJsonProperty(const String &name, const String &value)
{
    return "{\"" + name + "\":" + value + "}";
}