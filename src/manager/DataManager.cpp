/*
 *   DataManager.cpp
 *   ----------------------
 *   Created on: 2023/10/09
 *   Author: Lankow
 */
#include <vector>
#include "manager/DataManager.hpp"
#include "Logger.hpp"

Status DataManager::checkHumidity()
{
    Status result = Status::OK;

    const std::vector<HumidityData> humidityData = m_dataProvider->getHumidityData();

    for (int i = 0; i < MAX_SENSORS_NO; i++)
    {
        if (humidityData[i].getCurrentHumidityLvl() < humidityData[i].getHumidityThreshold() && humidityData[i].getHumidityActive())
        {
            m_logger->log(Logger::INFO, "Needs Watering");
            m_dataProvider->setSensorToWater(i);
            return result;
        }
    }

    m_dataProvider->setSensorToWater(NO_SENSOR);
    return result;
}

void DataManager::init()
{
    m_logger->log(Logger::INFO, "DataManager - Init");
}

void DataManager::cyclic()
{
    m_logger->log(Logger::INFO, "DataManager - Cyclic Task");
    checkHumidity();
}