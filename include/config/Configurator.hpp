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

/**
 * @class Configurator
 * @brief A class for managing configuration settings for the Plant Master system.
 *
 * The Configurator class reads configuration settings from a JSON file stored on SPIFFS
 * and provides these settings to other components of the system.
 */
class Configurator
{
public:
    /**
     * @brief Constructs a new Configurator object.
     */
    Configurator();

    /**
     * @brief Initializes the Configurator by mounting SPIFFS and reading the configuration file.
     *
     * @return true if initialization is successful, false otherwise.
     */
    bool init();

    /**
     * @brief Gets the reader pins configuration.
     *
     * @return A vector of integers representing the reader pins.
     */
    std::vector<int> getReaderPins() const;

    /**
     * @brief Gets the thresholds configuration.
     *
     * @return A vector of integers representing the thresholds.
     */
    std::vector<int> getThresholds() const;

    /**
     * @brief Gets the DHT sensor pin configuration.
     *
     * @return An integer representing the DHT sensor pin.
     */
    int getDhtPin() const;

    /**
     * @brief Gets the water pump pin configuration.
     *
     * @return An integer representing the water pump pin.
     */
    int getWaterPumpPin() const;

    /**
     * @brief Updates the threshold value at the specified index.
     *
     * @param index The index of the threshold to update.
     * @param value The new threshold value.
     */
    void updateThreshold(int index, int value);

private:
    StaticJsonDocument<1024> m_jsonDoc; /**< JSON document for storing configuration data. */
    std::vector<int> m_readerPins;      /**< Vector of reader pins. */
    std::vector<int> m_thresholds;      /**< Vector of thresholds. */
    int m_dhtPin;                       /**< DHT sensor pin. */
    int m_waterPumpPin;                 /**< Water pump pin. */

    /**
     * @brief Initializes SPIFFS.
     *
     * @return true if SPIFFS is initialized successfully, false otherwise.
     */
    bool initSPIFFS();

    /**
     * @brief Reads the configuration file from SPIFFS.
     *
     * @return true if the configuration file is read successfully, false otherwise.
     */
    bool readConfigFile();

    /**
     * @brief Gets an integer value from the JSON document.
     *
     * @param key The key of the integer value.
     * @return The integer value.
     */
    int getIntValue(const String &key);

    /**
     * @brief Gets an array of integers from the JSON document.
     *
     * @param key The key of the integer array.
     * @return A vector of integers.
     */
    std::vector<int> getIntArray(const String &key);

    /**
     * @brief Writes the updated configuration to the file.
     */
    void writeConfigFile();
};

#endif // CONFIGURATOR_HPP
