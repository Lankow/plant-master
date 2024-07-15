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

class PlantMaster
{
public:
    explicit PlantMaster(std::shared_ptr<Configurator> configurator);

    bool init();
    void cyclic();

private:
    WiFiInitializer m_wiFiInitializer;
    ResetHandler m_resetHandler;
    bool m_isInitialized;

    std::shared_ptr<Configurator> m_configurator;
    std::shared_ptr<DataStorage> m_dataStorage;
    std::shared_ptr<DataHandler> m_dataHandler;
    std::shared_ptr<MQTTManager> m_mqttManager;

#ifdef PLANT_MASTER
    ServerManager m_serverManager;
    WateringManager m_wateringManager;
#else
    PlantHumidityHandler m_plantHumidityHandler;
    WaterPumpController m_waterPumpController;
    DHTReader m_dhtReader;
#endif
};

#endif // PLANT_MASTER_HPP