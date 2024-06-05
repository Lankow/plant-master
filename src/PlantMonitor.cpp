/*
 *   PlantMonitor.cpp
 *   ----------------------
 *   Created on: 2024/05/31
 *   Author: Lankow
 */
#include "PlantMonitor.hpp"
#include "Constants.hpp"

PlantMonitor::PlantMonitor()
    : m_wiFiInitializer(),
      m_mqttManager(),
      m_dhtReader(EspPins::PIN_21),
      m_plantHumidityReader(EspPins::PIN_34),
      m_valveController(EspPins::PIN_12),
      m_waterPumpController(EspPins::PIN_18){};

void PlantMonitor::init()
{
    if (m_wiFiInitializer.init())
    {
        Serial.println("Connected to WiFi successfully.");
        m_waterPumpController.init();
        m_mqttManager.init();
    }
};

void PlantMonitor::cyclic()
{
    m_mqttManager.cyclic();
    m_plantHumidityReader.readHumidity();
    m_dhtReader.readRoomHumidity();
    m_dhtReader.readRoomTemperature();
};
