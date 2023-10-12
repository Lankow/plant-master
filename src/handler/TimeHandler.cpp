/*
*   TimeHandler.cpp
*   ----------------------
*   Created on: 2023/09/27
*   Author: Lankow
*/
#include <Arduino.h>

#include "handler/TimeHandler.hpp"
#include "constants.hpp"
    
void TimeHandler::getTimeStamp(char time_buffer[]){
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Logger::log("Encountered Error when retrieving system time...");
    return;
  }

  strftime(time_buffer,80,"%x - %H:%M:%S", &timeinfo);
};