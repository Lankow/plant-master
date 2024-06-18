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

    // Getter methods for specific configuration values
#ifdef PLANT_MASTER
    std::vector<int> getReaderPins() const;
    std::vector<int> getThresholds() const;
#endif

private:
    bool initSPIFFS();
    void readConfigFile();
    int getIntValue(const String &key);
    std::vector<int> getIntArray(const String &key);

    StaticJsonDocument<512> m_jsonDoc;
#ifdef PLANT_MASTER
    std::vector<int> m_readerPins;
    std::vector<int> m_thresholds;
#endif
};

#endif // CONFIGURATOR_HPP