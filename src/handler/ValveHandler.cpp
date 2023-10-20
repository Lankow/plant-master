/*
*   ValveHandler.cpp
*   ----------------------
*   Created on: 2023/12/01
*   Author: Lankow
*/
#include "handler/ValveHandler.hpp"
#include "Logger.hpp"

void ValveHandler::handleValves(){
  uint8_t sensorToWater = getDataProvider()->getSensorToWater();
  
  if(sensorToWater != NO_SENSOR){
    /* Open Valve */
  }else{
    /* Close Valve */
  }
};

void ValveHandler::cyclic(){
    getLogger()->log(Logger::INFO, "ValveHandler - Cyclic Task");
  handleValves();
};