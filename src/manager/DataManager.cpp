/*
*   DataManager.cpp
*   ----------------------
*   Created on: 2023/10/09
*   Author: Lankow
*/
#include "manager/DataManager.hpp"

void DataManager::checkHumidity(){
  uint16_t* currentHumidityLvl = getDataProvider()->getCurrentHumidityLvl();
  uint16_t* humidityThreshold = getDataProvider()->getHumidityThreshold();
  bool* humidityActive = getDataProvider()->getHumidityActive();

    for (int i = 0; i < MAX_SENSORS_NO; i++) {
      if (currentHumidityLvl[i] < humidityThreshold[i] && humidityActive[i]){
        Logger::log("Needs Watering");
        getDataProvider()->setSensorToWater(i);
        return;
      }
  }
  getDataProvider()->setSensorToWater(NO_SENSOR);
};

void DataManager::cyclic(){
  checkHumidity();
};