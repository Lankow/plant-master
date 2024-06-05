/*
 *   PlantMaster.cpp
 *   ----------------------
 *   Created on: 2024/05/31
 *   Author: Lankow
 */
#include "PlantMaster.hpp"

PlantMaster::PlantMaster()
    : m_serverManager(),
      m_mqttManager(),
      m_wiFiInitializer(),
      m_dataStorage(){};

void PlantMaster::init()
{
    if (m_wiFiInitializer.init())
    {
        Serial.println("Connected to WiFi successfully.");
        m_serverManager.init();
        m_mqttManager.init();
    }
};

void PlantMaster::cyclic()
{
    m_serverManager.cyclic();
    m_mqttManager.cyclic();
};
