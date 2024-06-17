/*
 *   ConfigHandler.hpp
 *   ----------------------
 *   Created on: 2024/06/10
 *   Author: Lankow
 */
#ifndef CONFIG_HANDLER_HPP
#define CONFIG_HANDLER_HPP

#include <Arduino.h>
#include <SPIFFS.h>
#include <ArduinoJson.h>

class ConfigHandler
{
public:
    ConfigHandler();

    void init();
    int getIntValue(const String &key);

private:
    bool initSPIFFS();
    void readConfigFile();

    StaticJsonDocument<512> m_jsonDoc;
};

#endif // CONFIG_HANDLER_HPP