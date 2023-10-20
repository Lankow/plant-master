/*
*   JSONFormatter.cpp
*   ----------------------
*   Created on: 2023/10/20
*   Author: Lankow
*/
#include "JSONFormatter.hpp"

JSONFormatter::JSONFormatter(DataProvider *p_dataProvider):m_dataProvider(p_dataProvider) {};

String JSONFormatter::buildHumidityJson() {
    String jsonStr = "{\"humidity\":[";

    for (int i = 0; i < MAX_SENSORS_NO; i++) {
        jsonStr += "{\"lvl\":" + String(m_dataProvider->getCurrentHumidityLvl()[i]) + ",";
        jsonStr += "\"threshold\":" + String(m_dataProvider->getHumidityThreshold()[i]) + ",";
        jsonStr += "\"active\":" + String(m_dataProvider->getHumidityActive()[i]) + "}";

        if (i < MAX_SENSORS_NO - 1) {
            jsonStr += ",";
        }
    }

    jsonStr += "]}";

    return jsonStr;
}

String JSONFormatter::serialize(JSONType p_jsonType){
    switch (p_jsonType) {
        case ROOM_HUMIDITY:
            return "{\"room-humidity\":" + String(m_dataProvider->getTemperature()) + "}";
        case TEMPERATURE:
            return "{\"temperature\":" + String(m_dataProvider->getTemperature()) + "}";
        case SENSOR:
            return "{\"sensor\":" + String(m_dataProvider->getSensorToWater()) + "}";
        case TIME:
            return "{\"time\":" + String(m_dataProvider->getCurrentTime()) + "}";
        case HUMIDITY:
            return buildHumidityJson();
        default:
            return "{}";
    }
};