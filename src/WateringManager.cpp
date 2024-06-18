/*
 *   WateringManager.cpp
 *   ----------------------
 *   Created on: 2024/06/12
 *   Author: Lankow
 */
#include "WateringManager.hpp"
#include "PlantHumidityData.hpp"

WateringManager::WateringManager(std::shared_ptr<DataStorage> dataStorage, std::shared_ptr<MQTTManager> mqttManager)
    : m_dataStorage(dataStorage),
      m_mqttManager(mqttManager){};

void WateringManager::cyclic()
{
    checkHumidity();
};

void WateringManager::checkHumidity()
{
    const std::vector<PlantHumidityData> plantsHumidityData = m_dataStorage->getPlantsHumidityData();

    for (int i = 0; i < plantsHumidityData.size(); i++)
    {
        if (plantsHumidityData[i].getCurrentHumidity() < plantsHumidityData[i].getHumidityThreshold())
        {
            Serial.println("Watering needed");
            m_waterPumpActive = true;
            return;
        }
    }

    m_waterPumpActive = false;
}
