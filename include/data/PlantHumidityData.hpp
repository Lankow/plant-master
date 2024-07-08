/**
 * @file PlantHumidityData.hpp
 * @date   2024-05-30
 * @author Lankow
 * @version 1.0
 *
 * @brief This file contains the definition of the PlantHumidityData class.
 *
 * Stores information about the humidity of a plant, including its assigned pin,
 * current humidity, and humidity threshold.
 */
#ifndef PLANT_HUMIDITY_DATA_HPP
#define PLANT_HUMIDITY_DATA_HPP

#include <Arduino.h>

/**
 * @class PlantHumidityData
 * @brief A class to store and manage data related to plant humidity.
 *
 * This class stores information about the humidity of a plant, including its assigned pin,
 * current humidity, and humidity threshold.
 */
class PlantHumidityData
{
public:
    /**
     * @brief Constructs a new PlantHumidityData object.
     *
     * @param pin The pin number associated with the plant humidity sensor.
     * @param threshold The humidity threshold for the plant.
     */
    PlantHumidityData(uint8_t pin, uint16_t threshold);

    /**
     * @brief Gets the pin assigned to the plant.
     *
     * @return The pin number.
     */
    uint8_t getAssignedPin() const;

    /**
     * @brief Gets the current humidity of the plant.
     *
     * @return The current humidity.
     */
    uint16_t getCurrentHumidity() const;

    /**
     * @brief Gets the humidity threshold for the plant.
     *
     * @return The humidity threshold.
     */
    uint16_t getHumidityThreshold() const;

    /**
     * @brief Sets the pin assigned to the plant.
     *
     * @param pin The new pin number.
     */
    void setAssignedPin(uint8_t pin);

    /**
     * @brief Sets the current humidity of the plant.
     *
     * @param humidity The new current humidity.
     */
    void setCurrentHumidity(uint16_t humidity);

    /**
     * @brief Sets the humidity threshold for the plant.
     *
     * @param threshold The new humidity threshold.
     */
    void setHumidityThreshold(uint16_t threshold);

private:
    uint8_t m_assignedPin;        /**< The pin number assigned to the plant. */
    uint16_t m_currentHumidity;   /**< The current humidity of the plant. */
    uint16_t m_humidityThreshold; /**< The humidity threshold for the plant. */
};

#endif // PLANT_HUMIDITY_DATA_HPP