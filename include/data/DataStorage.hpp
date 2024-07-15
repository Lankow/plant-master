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

class DataStorage
{
public:
#ifdef PLANT_MASTER
    explicit DataStorage(std::shared_ptr<Configurator> configurator);

    const std::vector<PlantHumidityData> &getPlantsHumidityData() const;
    float getRoomTemperature() const;
    float getRoomHumidity() const;

    void setRoomTemperature(float roomTemperature);
    void setRoomHumidity(float roomHumidity);
    void setPlantHumidity(uint8_t pin, uint16_t humidity);
    void setHumidityThreshold(uint8_t pin, uint16_t threshold);
#endif

    DataStorage();

    bool isWaterPumpActive() const;
    uint8_t getActiveReaderPin() const;
    void setWaterPumpActive(bool isWaterPumpActive);
    void setActiveReaderPin(uint8_t activeReaderPin);

private:
#ifdef PLANT_MASTER
    std::shared_ptr<Configurator> m_configurator;
    std::vector<PlantHumidityData> m_plantsHumidityData;
    float m_roomTemperature;
    float m_roomHumidity;
#endif
    bool m_isWaterPumpActive;
    uint8_t m_activeReaderPin;
};

#endif // DATA_STORAGE_HPP