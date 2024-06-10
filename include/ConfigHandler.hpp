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

private:
    void createConfigFile();
    void readConfigFile();
    void deleteConfigFile();
};

#endif // CONFIG_HANDLER_HPP