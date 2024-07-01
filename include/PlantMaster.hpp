/*
 *   PlantMaster.hpp
 *   ----------------------
 *   Created on: 2024/05/31
 *   Author: Lankow
 */
#ifndef PLANT_MASTER_HPP
#define PLANT_MASTER_HPP

#include <Arduino.h>
#include <memory>
#include "WiFiInitializer.hpp"
#include "ServerManager.hpp"
#include "MQTTManager.hpp"
#include "WateringManager.hpp"
#include "DataStorage.hpp"
#include "DataHandler.hpp"
#include "Configurator.hpp"
#include "PlantHumidityHandler.hpp"
#include "DHTReader.hpp"
#include "WaterPumpController.hpp"
#include "ResetHandler.hpp"

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
