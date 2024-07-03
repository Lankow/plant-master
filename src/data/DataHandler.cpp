/*
 *   DataHandler.cpp
 *   ----------------------
 *   Created on: 2024/06/07
 *   Author: Lankow
 */
#include "data/DataHandler.hpp"
#include "utilities/StringParser.hpp"

DataHandler::DataHandler(std::shared_ptr<DataStorage> dataStorage) : m_dataStorage(dataStorage){};

void DataHandler::handleData(const std::string &topic, const std::string &payload)
{
#ifdef PLANT_MASTER
    if (topic.find(MQTT::PLANT_HUMIDITY) != std::string::npos)
    {
        int pin, plantHumidity;

        if (!StringParser::extractNumberFromString(topic, pin))
            return;

        if (StringParser::parseStringToInt(payload, plantHumidity) && plantHumidity >= 0 && plantHumidity <= 65535)
        {
            m_dataStorage->setPlantHumidity(pin, plantHumidity);
        }
    }
    else if (topic == MQTT::ROOM_HUMIDITY)
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
    else if (topic == MQTT::ROOM_TEMPERATURE)
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
#else
    if (topic == MQTT::WATER_ACTIVE)
    {
        if (payload == PumpState::ACTIVE)
        {
            Serial.println("Activate pump.");
            m_dataStorage->setWaterPumpActive(true);
        }
        else
        {
            Serial.println("Deactivate pump.");
            m_dataStorage->setWaterPumpActive(false);
        }
    }
    else if (topic == MQTT::WATER_PIN)
    {
        int pin;
        if (StringParser::parseStringToInt(payload, pin))
        {
            Serial.println("Active Reader pin:");
            Serial.println(pin);
            m_dataStorage->setActiveReaderPin(pin);
        }
    }
#endif
}
