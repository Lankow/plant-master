/*
 *   PlantMonitor.cpp
 *   ----------------------
 *   Created on: 2024/05/31
 *   Author: Lankow
 */
#include "PlantMonitor.hpp"
#include "Constants.hpp"

PlantMonitor::PlantMonitor(std::shared_ptr<Configurator> configurator)
    : m_wiFiInitializer(),
      m_isInitialized(false),
      m_dataHandler(std::make_shared<DataHandler>()),
      m_mqttManager(std::make_shared<MQTTManager>(m_dataHandler)),
      m_dhtReader(configurator, m_mqttManager),
      m_plantHumidityReader(configurator, m_mqttManager),
      m_valveController(configurator),
      m_waterPumpController(configurator){};

void PlantMonitor::init()
{
    if (m_wiFiInitializer.init())
    {
        Serial.println("Connected to WiFi successfully.");
        m_waterPumpController.init();
        m_mqttManager->init();
        m_dhtReader.init();
        m_isInitialized = true;
    }
};

void PlantMonitor::cyclic()
{
    if (m_isInitialized)
    {
        m_mqttManager->cyclic();
        m_dhtReader.cyclic();
        m_plantHumidityReader.cyclic();
    }
};
