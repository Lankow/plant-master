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

class PlantMaster
{
public:
    PlantMaster();

    void init();
    void cyclic();

private:
    WiFiInitializer m_wiFiInitializer;
    ServerManager m_serverManager;
    MQTTManager m_mqttManager;
    DataStorage m_dataStorage;
};

#endif // PLANT_MASTER_HPP