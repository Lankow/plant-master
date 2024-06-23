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
#include "PlantHumidityHandler.hpp"
#include "DHTReader.hpp"
#include "WaterPumpController.hpp"
#include "WiFiInitializer.hpp"
#include "MQTTManager.hpp"
#include "DataHandler.hpp"
#include "Configurator.hpp"

class PlantMonitor
{
public:
    PlantMonitor(std::shared_ptr<Configurator> configurator);

    void init();
    void cyclic();

private:
    std::shared_ptr<MQTTManager> m_mqttManager;
    std::shared_ptr<Configurator> m_configurator;
    std::shared_ptr<DataHandler> m_dataHandler;
    WiFiInitializer m_wiFiInitializer;
    PlantHumidityHandler m_plantHumidityHandler;
    DHTReader m_dhtReader;
    WaterPumpController m_waterPumpController;
    bool m_isInitialized;
};

#endif // PLANT_MONITOR_HPP