/**
 * @file Configurator.cpp
 * @date   2024-06-10
 * @author Lankow
 * @version 1.0
 *
 * @brief This file contains the implementation of the Configurator class.
 *
 * The Configurator class is responsible for reading configuration settings from
 * a JSON file stored on SPIFFS and providing these settings to other components.
 */
#include "config/Configurator.hpp"
#include "config/Constants.hpp"

Configurator::Configurator() : m_dhtPin(0), m_waterPumpPin(0) {}

bool Configurator::init()
{
    if (!initSPIFFS())
    {
        Serial.println("Failed to mount SPIFFS");
        return false;
    }

    if (!SPIFFS.exists(Config::PATH.c_str()))
    {
        Serial.println("Config file does not exist. Creating default config.");
        createDefaultConfigFile();
        return false;
    }

    return readConfigFile();
}

std::vector<int> Configurator::getReaderPins() const { return m_readerPins; }
std::vector<int> Configurator::getThresholds() const { return m_thresholds; }
int Configurator::getDhtPin() const { return m_dhtPin; }
int Configurator::getWaterPumpPin() const { return m_waterPumpPin; }
int Configurator::getOledMosiPin() const { return m_oledMosiPin; }
int Configurator::getOledClkPin() const { return m_oledClkPin; }
int Configurator::getOledDcPin() const { return m_oledDcPin; }
int Configurator::getOledCsPin() const { return m_oledCsPin; }
int Configurator::getOledResetPin() const { return m_oledResetPin; }

bool Configurator::initSPIFFS()
{
    if (!SPIFFS.begin(true))
    {
        Serial.println("An error occurred while mounting SPIFFS");
        return false;
    }
    Serial.println("SPIFFS mounted successfully");
    return true;
}

bool Configurator::readConfigFile()
{
    File file = SPIFFS.open(Config::PATH.c_str());
    if (!file)
    {
        Serial.println("Failed to open config file. Possible reasons: file system corruption, insufficient memory, or file does not exist.");
        return false;
    }

    DeserializationError error = deserializeJson(m_jsonDoc, file);
    file.close();

    if (error)
    {
        Serial.print("Failed to read file: ");
        Serial.println(error.c_str());
        return false;
    }

    Serial.println("Config file loaded successfully");
    m_readerPins = getIntArray(JSON::READER_PINS.c_str());

#ifdef PLANT_MASTER
    m_thresholds = getIntArray(JSON::THRESHOLDS.c_str());
    m_oledMosiPin = getIntValue(JSON::OLED_MOSI_PIN.c_str());
    m_oledClkPin = getIntValue(JSON::OLED_CLK_PIN.c_str());
    m_oledDcPin = getIntValue(JSON::OLED_DC_PIN.c_str());
    m_oledCsPin = getIntValue(JSON::OLED_CS_PIN.c_str());
    m_oledResetPin = getIntValue(JSON::OLED_RESET_PIN.c_str());
#else
    m_dhtPin = getIntValue(JSON::DHT_PIN.c_str());
    m_waterPumpPin = getIntValue(JSON::WATER_PUMP_PIN.c_str());
#endif

    return true;
}

int Configurator::getIntValue(const String &key)
{
    if (m_jsonDoc.containsKey(key) && m_jsonDoc[key].is<int>())
    {
        return m_jsonDoc[key].as<int>();
    }
    Serial.print("Invalid or missing key: ");
    Serial.println(key);
    return 0;
}

std::vector<int> Configurator::getIntArray(const String &key)
{
    std::vector<int> result;
    if (m_jsonDoc.containsKey(key) && m_jsonDoc[key].is<JsonArray>())
    {
        JsonArray array = m_jsonDoc[key].as<JsonArray>();
        for (JsonVariant value : array)
        {
            if (value.is<int>())
            {
                result.push_back(value.as<int>());
            }
            else
            {
                Serial.print("Invalid value in array for key: ");
                Serial.println(key);
            }
        }
    }
    else
    {
        Serial.print("Invalid or missing key: ");
        Serial.println(key);
    }
    return result;
}

void Configurator::updateThreshold(int index, int value)
{
    if (index >= 0 && index < m_thresholds.size())
    {
        m_thresholds[index] = value;
        m_jsonDoc[JSON::THRESHOLDS.c_str()].clear();
        for (int threshold : m_thresholds)
        {
            m_jsonDoc[JSON::THRESHOLDS.c_str()].add(threshold);
        }
        writeConfigFile();
    }
    else
    {
        Serial.println("Index out of range");
    }
}

void Configurator::writeConfigFile()
{
    File file = SPIFFS.open(Config::PATH.c_str(), FILE_WRITE);
    if (!file)
    {
        Serial.println("Failed to open config file for writing");
        return;
    }

    if (serializeJson(m_jsonDoc, file) == 0)
    {
        Serial.println("Failed to write to config file");
    }
    else
    {
        Serial.println("Config file updated successfully");
    }
    file.close();
}

void Configurator::createDefaultConfigFile() {}
