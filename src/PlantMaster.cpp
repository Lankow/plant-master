/*
 *   PlantMaster.cpp
 *   ----------------------
 *   Created on: 2024/05/31
 *   Author: Lankow
 */
#include "PlantMaster.hpp"

PlantMaster::PlantMaster()
    : m_displayRenderer(std::make_shared<DisplayRenderer>()),
      m_serverManager(m_displayRenderer),
      m_wiFiInitializer(m_displayRenderer, 80),
      m_dataStorage(){};

void PlantMaster::init()
{
    if (m_wiFiInitializer.connectToSavedWiFiOrSetupAP())
    {
        Serial.println("Connected to WiFi successfully.");
        m_serverManager.init();
    }
};

void PlantMaster::cyclic()
{
    m_serverManager.cyclic();
};
