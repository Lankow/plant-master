/*
*   DataManager.cpp
*   ----------------------
*   Created on: 2023/10/09
*   Author: Lankow
*/
#include "manager/DataManager.hpp"
#include "HumidityData.hpp"

void DataManager::checkHumidity(){
  HumidityData* humidityData = getDataProvider()->getHumidityData();

    for (int i = 0; i < MAX_SENSORS_NO; i++) {
      if (humidityData[i].getCurrentHumidityLvl() < humidityData[i].getHumidityThreshold()) {
        Serial.println("Needs Watering");
        humidityData[i].setNeedsWatering(true);
      }else{
        Serial.println("Does not need Watering");
        humidityData[i].setNeedsWatering(false);
      }
  }

};

void DataManager::cyclic(){
  checkHumidity();
};