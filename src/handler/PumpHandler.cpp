/*
*   PumpHandler.cpp
*   ----------------------
*   Created on: 2023/10/10
*   Author: Lankow
*/
#include "handler/PumpHandler.hpp"
#include "Logger.hpp"

void PumpHandler::handlePump(){
  uint8_t sensorToWater = getDataProvider()->getSensorToWater();
  if(sensorToWater != NO_SENSOR){
    /* Launch Pump */
  }else{
    /* Turn off Pump */
  }
};

void PumpHandler::cyclic(){
  getLogger()->log(Logger::INFO, "PumpHandler - Cyclic Task");
  handlePump();
};