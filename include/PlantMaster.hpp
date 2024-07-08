/**
 * @file PlantMaster.hpp
 * @date   2024-05-31
 * @author Lankow
 * @version 1.0
 *
 * @brief This file contains the definition of the PlantMaster class.
 *
 * The PlantMaster class is responsible for initializing and managing the core components
 * of the Plant Master system, including network initialization, data handling, and
 * managing various sensors and controllers.
 */
#ifndef PLANT_MASTER_HPP
#define PLANT_MASTER_HPP

#include <Arduino.h>
#include <memory>
#include "network/WiFiInitializer.hpp"
#include "network/ServerManager.hpp"
#include "network/MQTTManager.hpp"
#include "core/WateringManager.hpp"
#include "data/DataStorage.hpp"
#include "data/DataHandler.hpp"
#include "config/Configurator.hpp"
#include "core/PlantHumidityHandler.hpp"
#include "core/DHTReader.hpp"
#include "core/WaterPumpController.hpp"
#include "core/ResetHandler.hpp"

/**
 * @class PlantMaster
 * @brief A class for managing the initialization and cyclic operation of the Plant Master system.
 *
 * The PlantMaster class handles the initialization of network components, data storage,
 * and various sensors and controllers. It also manages the cyclic operation of these components.
 */
class PlantMaster
{
public:
    /**
     * @brief Constructs a new PlantMaster object.
     *
     * @param configurator A shared pointer to a Configurator object for configuration settings.
     */
    explicit PlantMaster(std::shared_ptr<Configurator> configurator);

    /**
     * @brief Initializes the PlantMaster system.
     *
     * This method initializes the WiFi, MQTT, and other necessary components.
     *
     * @return true if the initialization was successful, false otherwise.
     */
    bool init();

    /**
     * @brief Performs cyclic operations for the PlantMaster system.
     *
     * This method should be called periodically to ensure that all components
     * perform their necessary cyclic operations.
     */
    void cyclic();

private:
    WiFiInitializer m_wiFiInitializer; /**< Object to manage WiFi initialization. */
    ResetHandler m_resetHandler;       /**< Object to handle system resets. */
    bool m_isInitialized;              /**< Flag to indicate if the system is initialized. */

    std::shared_ptr<Configurator> m_configurator; /**< Shared pointer to the Configurator object. */
    std::shared_ptr<DataStorage> m_dataStorage;   /**< Shared pointer to the DataStorage object. */
    std::shared_ptr<DataHandler> m_dataHandler;   /**< Shared pointer to the DataHandler object. */
    std::shared_ptr<MQTTManager> m_mqttManager;   /**< Shared pointer to the MQTTManager object. */

#ifdef PLANT_MASTER
    ServerManager m_serverManager;     /**< Object to manage the server. */
    WateringManager m_wateringManager; /**< Object to manage watering. */
#else
    PlantHumidityHandler m_plantHumidityHandler; /**< Object to handle plant humidity. */
    WaterPumpController m_waterPumpController;   /**< Object to control the water pump. */
    DHTReader m_dhtReader;                       /**< Object to read DHT sensor data. */
#endif
};

#endif // PLANT_MASTER_HPP