/*
 *   PlantMaster.cpp
 *   ----------------------
 *   Created on: 2024/05/31
 *   Author: Lankow
 */
#include "PlantMaster.hpp"

PlantMaster::PlantMaster()
    : m_dataStorage(std::make_shared<DataStorage>()),
      m_dataHandler(std::make_shared<DataHandler>(m_dataStorage)),
      m_mqttManager(m_dataHandler),
      m_serverManager(),
      m_wiFiInitializer(){};

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
