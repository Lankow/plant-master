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
#ifdef PLANT_MASTER
    const std::vector<PlantHumidityData> plantsHumidityData = m_dataStorage->getPlantsHumidityData();

    for (int i = 0; i < plantsHumidityData.size(); i++)
    {
        if (plantsHumidityData[i].getCurrentHumidity() < plantsHumidityData[i].getHumidityThreshold())
        {
            Serial.println("Watering needed");
            m_mqttManager->publish(MQTT_WATER_ACTIVE, PUMP_ACTIVE, 0, false);
            m_mqttManager->publish(MQTT_WATER_PIN, std::to_string(plantsHumidityData[i].getAssignedPin()), 0, false);

            return;
        }
    }

    m_mqttManager->publish(MQTT_WATER_ACTIVE, PUMP_INACTIVE, 0, false);
#endif
}
