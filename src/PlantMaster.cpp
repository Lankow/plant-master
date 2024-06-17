/*
 *   PlantMaster.cpp
 *   ----------------------
 *   Created on: 2024/05/31
 *   Author: Lankow
 */
#include "PlantMaster.hpp"

PlantMaster::PlantMaster(std::shared_ptr<Configurator> configurator)
    : m_dataStorage(std::make_shared<DataStorage>()),
      m_dataHandler(std::make_shared<DataHandler>(m_dataStorage)),
      m_serverManager(m_dataStorage),
      m_mqttManager(std::make_shared<MQTTManager>(m_dataHandler)),
      m_wiFiInitializer(),
      m_wateringManager(m_dataStorage, m_mqttManager),
      m_isInitialized(false){};

void PlantMaster::init()
{
    if (m_wiFiInitializer.init())
    {
        Serial.println("Connected to WiFi successfully.");
        m_serverManager.init();
        m_mqttManager->init();

        m_isInitialized = true;
    }
};

void PlantMaster::cyclic()
{
    if (m_isInitialized)
    {
        m_serverManager.cyclic();
        m_mqttManager->cyclic();
        m_wateringManager.cyclic();
    }
};
