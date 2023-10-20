/*
*   TimeHandler.cpp
*   ----------------------
*   Created on: 2023/09/27
*   Author: Lankow
*/
#include <Arduino.h>

#include "handler/TimeHandler.hpp"
#include "constants.hpp"
#include "Logger.hpp"

void TimeHandler::handleTime(){
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
      getLogger()->log(Logger::ERROR, "Encountered Error when retrieving system time...");
    return;
  }
  getDataProvider()->setCurrentTime(timeinfo);
};

void TimeHandler::init(){
  getLogger()->log(Logger::INFO, "TimeHandler - Init");
  for(int i=0; i<MAX_RETRIES; i++){
    handleTime();
    if(getDataProvider()->getCurrentTime() != DEFAULT_TIME) return;
    delay(1000);
  }
}

void TimeHandler::cyclic(){
  getLogger()->log(Logger::INFO, "TimeHandler - Cyclic Task");
  handleTime();
}