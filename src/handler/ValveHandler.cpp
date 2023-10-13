/*
*   ValveHandler.cpp
*   ----------------------
*   Created on: 2023/12/01
*   Author: Lankow
*/
#include "handler/ValveHandler.hpp"

void ValveHandler::handleValves(){
  uint8_t sensorToWater = getDataProvider()->getSensorToWater();
  
  if(sensorToWater != NO_SENSOR){
    /* Open Valve */
  }else{
    /* Close Valve */
  }
};

void ValveHandler::cyclic(){
  Logger::log("ValveHandler - Cyclic Task");
  handleValves();
};
