/*
 *   WateringManager.cpp
 *   ----------------------
 *   Created on: 2023/10/09
 *   Author: Lankow
 */
#include <vector>
#include "manager/WateringManager.hpp"
#include "utils/Logger.hpp"

Status WateringManager::checkHumidity()
{
    Status result = Status::OK;

    const std::vector<HumidityData> humidityData = m_dataProvider->getHumidityData();

    for (int i = 0; i < MAX_SENSORS_NO; i++)
    {
        if (humidityData[i].getCurrentHumidityLvl() < humidityData[i].getHumidityThreshold() && humidityData[i].getHumidityActive())
        {
            Logger::log(Logger::INFO, "Needs Watering");
            m_dataProvider->setSensorToWater(i);
            return result;
        }
    }

    m_dataProvider->setSensorToWater(NO_SENSOR);
    return result;
}

void WateringManager::init()
{
    Logger::log(Logger::INFO, "WateringManager - Init");
}

void WateringManager::cyclic()
{
    Logger::log(Logger::INFO, "WateringManager - Cyclic Task");
    checkHumidity();
}