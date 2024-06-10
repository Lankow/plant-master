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
#include "DataStorage.hpp"
#include "DataHandler.hpp"
#include "ConfigHandler.hpp"
class PlantMaster
{
public:
    PlantMaster();

    void init();
    void cyclic();

private:
    std::shared_ptr<DataStorage> m_dataStorage;
    std::shared_ptr<DataHandler> m_dataHandler;
    WiFiInitializer m_wiFiInitializer;
    ServerManager m_serverManager;
    MQTTManager m_mqttManager;
    ConfigHandler m_configHandler;
};

#endif // PLANT_MASTER_HPP