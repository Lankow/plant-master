/**
 * @file DataStorage.hpp
 * @date   2024-05-30
 * @author Lankow
 * @version 1.0
 *
 * @brief This file contains the definition of the DataStorage class.
 *
 * This class handles the storage and management of data related to plants, room conditions,
 * and the water pump state.
 */
#ifndef DATA_STORAGE_HPP
#define DATA_STORAGE_HPP

#include <Arduino.h>
#include <vector>
#include <memory>
#include "data/PlantHumidityData.hpp"
#include "config/Configurator.hpp"
#include "config/Constants.hpp"

/**
 * @class DataStorage
 * @brief A class to manage storage of various data.
 *
 * This class handles the storage and management of data related to plants, room conditions,
 * and the water pump state.
 */
class DataStorage
{
public:
#ifdef PLANT_MASTER
    /**
     * @brief Constructs a new DataStorage object.
     *
     * @param configurator A shared pointer to a Configurator object for configuration settings.
     */
    explicit DataStorage(std::shared_ptr<Configurator> configurator);

    /**
     * @brief Gets the humidity data for all plants.
     *
     * @return A reference to a vector of PlantHumidityData objects.
     */
    const std::vector<PlantHumidityData> &getPlantsHumidityData() const;

    /**
     * @brief Gets the current room temperature.
     *
     * @return The current room temperature.
     */
    float getRoomTemperature() const;

    /**
     * @brief Gets the current room humidity.
     *
     * @return The current room humidity.
     */
    float getRoomHumidity() const;

    /**
     * @brief Sets the current room temperature.
     *
     * @param roomTemperature The new room temperature.
     */
    void setRoomTemperature(float roomTemperature);

    /**
     * @brief Sets the current room humidity.
     *
     * @param roomHumidity The new room humidity.
     */
    void setRoomHumidity(float roomHumidity);

    /**
     * @brief Sets the current humidity for a specific plant.
     *
     * @param pin The pin number associated with the plant.
     * @param humidity The new humidity value.
     */
    void setPlantHumidity(uint8_t pin, uint16_t humidity);

    /**
     * @brief Sets the humidity threshold for a specific plant.
     *
     * @param pin The pin number associated with the plant.
     * @param threshold The new humidity threshold.
     */
    void setHumidityThreshold(uint8_t pin, uint16_t threshold);
#endif

    /**
     * @brief Default constructor for DataStorage.
     */
    DataStorage();

    /**
     * @brief Checks if the water pump is active.
     *
     * @return True if the water pump is active, false otherwise.
     */
    bool isWaterPumpActive() const;

    /**
     * @brief Gets the pin number of the active reader.
     *
     * @return The pin number of the active reader.
     */
    uint8_t getActiveReaderPin() const;

    /**
     * @brief Sets the water pump active state.
     *
     * @param isWaterPumpActive The new water pump active state.
     */
    void setWaterPumpActive(bool isWaterPumpActive);

    /**
     * @brief Sets the pin number of the active reader.
     *
     * @param activeReaderPin The new pin number of the active reader.
     */
    void setActiveReaderPin(uint8_t activeReaderPin);

private:
#ifdef PLANT_MASTER
    std::shared_ptr<Configurator> m_configurator;        /**< A shared pointer to a Configurator object. */
    std::vector<PlantHumidityData> m_plantsHumidityData; /**< A vector of PlantHumidityData objects. */
    float m_roomTemperature;                             /**< The current room temperature. */
    float m_roomHumidity;                                /**< The current room humidity. */
#endif
    bool m_isWaterPumpActive;  /**< The current state of the water pump. */
    uint8_t m_activeReaderPin; /**< The pin number of the active reader. */
};

#endif // DATA_STORAGE_HPP