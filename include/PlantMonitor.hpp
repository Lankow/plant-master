/*
 *   PlantMonitor.hpp
 *   ----------------------
 *   Created on: 2024/05/31
 *   Author: Lankow
 */
#ifndef PLANT_MONITOR_HPP
#define PLANT_MONITOR_HPP

#include <Arduino.h>
#include <memory>
#include "PlantHumidityReader.hpp"
#include "DHTReader.hpp"
#include "WaterPumpController.hpp"
#include "ValveController.hpp"
#include "WiFiInitializer.hpp"
#include "MQTTManager.hpp"
#include "DataHandler.hpp"
#include "ConfigHandler.hpp"

class PlantMonitor
{
public:
    PlantMonitor(std::shared_ptr<ConfigHandler> configHandler);

    void init();
    void cyclic();

private:
    std::shared_ptr<MQTTManager> m_mqttManager;
    std::shared_ptr<DataHandler> m_dataHandler;
    std::shared_ptr<ConfigHandler> m_configHandler;
    WiFiInitializer m_wiFiInitializer;
    PlantHumidityReader m_plantHumidityReader;
    DHTReader m_dhtReader;
    WaterPumpController m_waterPumpController;
    ValveController m_valveController;
};

#endif // PLANT_MONITOR_HPP