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
      m_mqttManager(mqttManager)
{
}

void WateringManager::cyclic()
{
    checkHumidity();
}

void WateringManager::checkHumidity()
{
#ifdef PLANT_MASTER
    const std::vector<PlantHumidityData> plantsHumidityData = m_dataStorage->getPlantsHumidityData();

    for (const auto &plantData : plantsHumidityData)
    {
        if (plantData.getCurrentHumidity() < plantData.getHumidityThreshold())
        {
            Serial.println("Watering needed");
            m_dataStorage->setWaterPumpActive(true);
            m_mqttManager->publish(MQTT::WATER_ACTIVE, PumpState::ACTIVE, 0, false);
            m_mqttManager->publish(MQTT::WATER_PIN, std::to_string(plantData.getAssignedPin()), 0, false);
            m_dataStorage->setActiveReaderPin(plantData.getAssignedPin());
            return;
        }
    }
    m_mqttManager->publish(MQTT::WATER_ACTIVE, PumpState::INACTIVE, 0, false);
    m_dataStorage->setWaterPumpActive(false);
    m_dataStorage->setActiveReaderPin(HumiditySensor::DEFAULT_ACTIVE_PIN);
#endif
}