/*
 *   DataHandler.cpp
 *   ----------------------
 *   Created on: 2024/06/07
 *   Author: Lankow
 */
#include "DataHandler.hpp"
#include "StringParser.hpp"

#ifdef PLANT_MASTER
DataHandler::DataHandler(std::shared_ptr<DataStorage> dataStorage) : m_dataStorage(dataStorage){};
#else
DataHandler::DataHandler(){};
#endif

void DataHandler::handleData(const std::string &topic, const std::string &payload)
{
#ifdef PLANT_MASTER
    if (topic == MQTT_PLANT_HUMIDITY)
    {
        int plantHumidity;
        if (StringParser::parseStringToInt(payload, plantHumidity) && plantHumidity >= 0 && plantHumidity <= 65535)
        {
            m_dataStorage->setPlantHumidity(0, static_cast<uint16_t>(plantHumidity));
            Serial.println(plantHumidity);
        }
        else
        {
            Serial.println("Failed to parse plant humidity: ");
            Serial.println(payload.c_str());
        }
    }
    else if (topic == MQTT_ROOM_HUMIDITY)
    {
        float roomHumidity;
        if (StringParser::parseStringToFloat(payload, roomHumidity))
        {
            Serial.println(roomHumidity);
            m_dataStorage->setRoomHumidity(roomHumidity);
        }
        else
        {
            Serial.println("Failed to parse room humidity: ");
            Serial.println(payload.c_str());
        }
    }
    else if (topic == MQTT_ROOM_TEMPERATURE)
    {
        float roomTemperature;
        if (StringParser::parseStringToFloat(payload, roomTemperature))
        {
            Serial.println(roomTemperature);
            m_dataStorage->setRoomTemperature(roomTemperature);
        }
        else
        {
            Serial.println("Failed to parse room temperature: ");
            Serial.println(payload.c_str());
        }
    }
#endif
}
