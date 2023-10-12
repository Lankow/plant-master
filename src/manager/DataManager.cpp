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

    for (int i = 0; i < MAX_SENSORS_NO; i++) {
      if (currentHumidityLvl[i] < humidityThreshold[i]) {
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