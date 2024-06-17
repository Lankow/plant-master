/*
 *   ConfigHandler.hpp
 *   ----------------------
 *   Created on: 2024/06/10
 *   Author: Lankow
 */
#include "ConfigHandler.hpp"
#include "Constants.hpp"

ConfigHandler::ConfigHandler(){};

void ConfigHandler::init()
{
    if (!initSPIFFS())
    {
        Serial.println("An error has occurred while mounting SPIFFS");
        return;
    }
    Serial.println("SPIFFS mounted successfully");

    if (!SPIFFS.exists(CONFIG_PATH.c_str()))
    {
        Serial.println("Config file does not exist. Please rebuild project.");
        return;
    }

    readConfigFile();
}

bool ConfigHandler::initSPIFFS()
{
    if (!SPIFFS.begin(true))
    {
        return false;
    }
    return true;
}

void ConfigHandler::readConfigFile()
{
    File file = SPIFFS.open(CONFIG_PATH.c_str());
    if (!file)
    {
        Serial.println("Failed to open Config file");
        return;
    }

    DeserializationError error = deserializeJson(m_jsonDoc, file);
    if (error)
    {
        Serial.print("Failed to read file: ");
        Serial.println(error.c_str());
    }
    else
    {
        Serial.println("Config file loaded successfully");
    }

    file.close();
}

int ConfigHandler::getIntValue(const String &key)
{
    if (m_jsonDoc.containsKey(key))
    {
        if (m_jsonDoc[key].is<int>())
        {
            return m_jsonDoc[key].as<int>();
        }
        else
        {
            Serial.print("Value for key ");
            Serial.print(key);
            Serial.println(" is not an integer.");
            return 0;
        }
    }
    else
    {
        Serial.print("Key not found: ");
        Serial.println(key);
        return 0;
    }
}
