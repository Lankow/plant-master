/**
 * @file Configurator.hpp
 * @date   2024-06-10
 * @author Lankow
 * @version 1.0
 *
 * @brief This file contains the definition of the Configurator class.
 *
 * The Configurator class is responsible for reading configuration settings from
 * a JSON file stored on SPIFFS and providing these settings to other components.
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
    int getOledMosiPin() const;
    int getOledClkPin() const;
    int getOledDcPin() const;
    int getOledCsPin() const;
    int getOledResetPin() const;

    void updateThreshold(int index, int value);

private:
    StaticJsonDocument<1024> m_jsonDoc;
    std::vector<int> m_readerPins;
    std::vector<int> m_thresholds;
    int m_dhtPin;
    int m_waterPumpPin;
    int m_oledMosiPin;
    int m_oledClkPin;
    int m_oledDcPin;
    int m_oledCsPin;
    int m_oledResetPin;

    bool initSPIFFS();
    bool readConfigFile();

    int getIntValue(const String &key);
    std::vector<int> getIntArray(const String &key);
    void writeConfigFile();
};

#endif // CONFIGURATOR_HPP
