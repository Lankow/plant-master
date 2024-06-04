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

class PlantMonitor
{
public:
    PlantMonitor();

    void init();
    void cyclic();

private:
    WiFiInitializer m_wiFiInitializer;
    PlantHumidityReader m_plantHumidityReader;
    DHTReader m_dhtReader;
    WaterPumpController m_waterPumpController;
    ValveController m_valveController;
};

#endif // PLANT_MONITOR_HPP