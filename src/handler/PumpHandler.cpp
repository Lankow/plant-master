/*
*   PumpHandler.cpp
*   ----------------------
*   Created on: 2023/10/10
*   Author: Lankow
*/
#include "handler/PumpHandler.hpp"

void PumpHandler::handlePump(){
  uint8_t sensorToWater = getDataProvider()->getSensorToWater();
  if(sensorToWater != NO_SENSOR){
    /* Launch Pump */
  }else{
    /* Turn off Pump */
  }
};

void PumpHandler::cyclic(){
  handlePump();
};