/*
 *   Configurator.hpp
 *   ----------------------
 *   Created on: 2024/06/10
 *   Author: Lankow
 */
#ifndef CONFIGURATOR_HPP
#define CONFIGURATOR_HPP

#include <Arduino.h>
#include <SPIFFS.h>
#include <ArduinoJson.h>
#include <vector>

class Configurator
{
public:
    Configurator();

    void init();
    int getIntValue(const String &key);
    std::vector<int> getIntArray(const String &key);

private:
    bool initSPIFFS();
    void readConfigFile();

    StaticJsonDocument<512> m_jsonDoc;
};

#endif // CONFIGURATOR_HPP