/*
*   TimeHandler.cpp
*   ----------------------
*   Created on: 2023/09/27
*   Author: Lankow
*/
#include <Arduino.h>

#include "handler/TimeHandler.hpp"
#include "constants.hpp"
    
void TimeHandler::handleTimestamp(){
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Logger::log("Encountered Error when retrieving system time...");
    return;
  }
  getDataProvider()->setCurrentTime(timeinfo);
};

void TimeHandler::cyclic(){
  handleTimestamp();
}