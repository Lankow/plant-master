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
};

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

    StaticJsonDocument<200> jsonDoc;
    DeserializationError error = deserializeJson(jsonDoc, file);
    if (error)
    {
        Serial.print("Failed to read file, using default configuration: ");
        Serial.println(error.c_str());
    }

    const char *version = jsonDoc["version"];

    Serial.print("Config version: ");
    Serial.println(version);

    file.close();
};
