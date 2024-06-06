/*
 *   PlantMonitor.cpp
 *   ----------------------
 *   Created on: 2024/05/31
 *   Author: Lankow
 */
#include "PlantMonitor.hpp"
#include "Constants.hpp"

PlantMonitor::PlantMonitor()

    : m_mqttManager(std::make_shared<MQTTManager>()),
      m_wiFiInitializer(),
      m_dhtReader(EspPins::PIN_21, m_mqttManager),
      m_plantHumidityReader(EspPins::PIN_34, m_mqttManager),
      m_valveController(EspPins::PIN_12),
      m_waterPumpController(EspPins::PIN_18){};

void PlantMonitor::init()
{
    if (m_wiFiInitializer.init())
    {
        Serial.println("Connected to WiFi successfully.");
        m_waterPumpController.init();
        m_mqttManager->init();
    }
};

void PlantMonitor::cyclic()
{
    m_mqttManager->cyclic();
    m_dhtReader.cyclic();
    m_plantHumidityReader.cyclic();
};
