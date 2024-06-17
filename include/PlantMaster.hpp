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

class PlantMaster
{
public:
    PlantMaster(std::shared_ptr<Configurator> configurator);

    void init();
    void cyclic();

private:
    std::shared_ptr<DataStorage> m_dataStorage;
    std::shared_ptr<DataHandler> m_dataHandler;
    std::shared_ptr<MQTTManager> m_mqttManager;
    WiFiInitializer m_wiFiInitializer;
    ServerManager m_serverManager;
    WateringManager m_wateringManager;

    bool m_isInitialized;
};

#endif // PLANT_MASTER_HPP