/*
 *   PlantMaster.cpp
 *   ----------------------
 *   Created on: 2024/05/31
 *   Author: Lankow
 */
#include "PlantMaster.hpp"

PlantMaster::PlantMaster(std::shared_ptr<Configurator> configurator)
#ifdef PLANT_MASTER
    : m_isInitialized(false),
      m_wiFiInitializer(),
      m_resetHandler(),
      m_dataStorage(std::make_shared<DataStorage>(configurator)),
      m_dataHandler(std::make_shared<DataHandler>(m_dataStorage)),
      m_serverManager(m_dataStorage),
      m_mqttManager(std::make_shared<MQTTManager>(m_dataHandler, configurator)),
      m_wateringManager(m_dataStorage, m_mqttManager){};
#else
    : m_isInitialized(false),
      m_wiFiInitializer(),
      m_resetHandler(),
      m_dataStorage(std::make_shared<DataStorage>()),
      m_dataHandler(std::make_shared<DataHandler>(m_dataStorage)),
      m_mqttManager(std::make_shared<MQTTManager>(m_dataHandler)),
      m_dhtReader(configurator, m_mqttManager),
      m_plantHumidityHandler(configurator, m_mqttManager),
      m_waterPumpController(configurator){};
#endif

void PlantMaster::init()
{
    if (m_wiFiInitializer.init())
    {
        Serial.println("Connected to WiFi successfully.");
        m_mqttManager->init();
        m_resetHandler.init();
#ifdef PLANT_MASTER
        m_serverManager.init();
#else
        m_waterPumpController.init();
        m_dhtReader.init();
#endif
        m_isInitialized = true;
    }
};

void PlantMaster::cyclic()
{
    m_resetHandler.cyclic();

    if (m_isInitialized)
    {
        m_mqttManager->cyclic();
#ifdef PLANT_MASTER
        m_serverManager.cyclic();
        m_wateringManager.cyclic();
#else
        m_dhtReader.cyclic();
        m_plantHumidityHandler.cyclic();
#endif
    }
};
