/*
*   TimeHandler.cpp
*   ----------------------
*   Created on: 2023/09/27
*   Author: Lankow
*/
#include <Arduino.h>

#include "TimeHandler.h"
#include "constants.h"
    
void TimeHandler::getTimeStamp(){
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Encountered Error when retrieving system time...");
    return;
  }

  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
};