/*
 *   DataManager.cpp
 *   ----------------------
 *   Created on: 2023/10/09
 *   Author: Lankow
 */
#include "manager/DataManager.hpp"
#include "Logger.hpp"

void DataManager::checkHumidity()
{
    DataProvider *dataProvider = getDataProvider();

    uint16_t *currentHumidityLvl = dataProvider->getCurrentHumidityLvl();
    uint16_t *humidityThreshold = dataProvider->getHumidityThreshold();
    bool *humidityActive = dataProvider->getHumidityActive();

    for (int i = 0; i < MAX_SENSORS_NO; i++)
    {
        if (currentHumidityLvl[i] < humidityThreshold[i] && humidityActive[i])
        {
            getLogger()->log(Logger::INFO, "Needs Watering");
            dataProvider->setSensorToWater(i);
            return; // Early return when a sensor needs watering
        }
    }

    dataProvider->setSensorToWater(NO_SENSOR);
}

void DataManager::cyclic()
{
    checkHumidity();
}