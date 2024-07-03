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

    bool init();

    std::vector<int> getReaderPins() const;
    std::vector<int> getThresholds() const;
    int getDhtPin() const;
    int getWaterPumpPin() const;
    void updateThreshold(int index, int value);

private:
    bool initSPIFFS();
    bool readConfigFile();
    int getIntValue(const String &key);
    std::vector<int> getIntArray(const String &key);
    void writeConfigFile();

    StaticJsonDocument<1024> m_jsonDoc;
    std::vector<int> m_readerPins;
    std::vector<int> m_thresholds;
    int m_dhtPin;
    int m_waterPumpPin;
};

#endif // CONFIGURATOR_HPP
