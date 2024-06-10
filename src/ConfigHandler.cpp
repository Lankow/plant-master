/*
 *   ConfigHandler.hpp
 *   ----------------------
 *   Created on: 2024/06/10
 *   Author: Lankow
 */
#include "ConfigHandler.hpp"

ConfigHandler::ConfigHandler(){};

void ConfigHandler::init()
{
    if (!SPIFFS.begin(true))
    {
        Serial.println("An error has occurred while mounting SPIFFS");
        return;
    }
    Serial.println("SPIFFS mounted successfully");

    if (!SPIFFS.exists("/config.json"))
    {
        Serial.println("config.json does not exist. Creating file...");
        createConfigFile();
    }
    else
    {
        Serial.println("config.json exists.");
        deleteConfigFile();
        return;
    }

    readConfigFile();
};

void ConfigHandler::createConfigFile()
{
    StaticJsonDocument<200> jsonDoc;
    jsonDoc["threshold"] = "4095";

    File file = SPIFFS.open("/config.json", FILE_WRITE);
    if (!file)
    {
        Serial.println("Failed to create config.json");
        return;
    }

    if (serializeJson(jsonDoc, file) == 0)
    {
        Serial.println("Failed to write to config.json");
    }
    else
    {
        Serial.println("config.json created successfully");
    }

    file.close();
};

void ConfigHandler::readConfigFile()
{
    File file = SPIFFS.open("/config.json");
    if (!file)
    {
        Serial.println("Failed to open config.json");
        return;
    }

    StaticJsonDocument<200> jsonDoc;
    DeserializationError error = deserializeJson(jsonDoc, file);
    if (error)
    {
        Serial.print("Failed to read file, using default configuration: ");
        Serial.println(error.c_str());
    }

    const char *threshold = jsonDoc["threshold"];

    Serial.println("Config settings:");
    Serial.print("Threshold: ");
    Serial.println(threshold);

    file.close();
};

void ConfigHandler::deleteConfigFile()
{
    if (SPIFFS.exists("/config.json"))
    {
        if (SPIFFS.remove("/config.json"))
        {
            Serial.println("config.json deleted successfully");
        }
        else
        {
            Serial.println("Failed to delete config.json");
        }
    }
    else
    {
        Serial.println("config.json does not exist");
    }
}
