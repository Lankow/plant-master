/*
*   HumidityHandler.cpp
*   ----------------------
*   Created on: 2023/09/26
*   Author: Lankow
*/
#include "handler/HumidityHandler.hpp"
#include "constants.hpp"

HumidityHandler::HumidityHandler(uint8_t p_operatedPin):
                                 m_operatedPin(p_operatedPin){};

void HumidityHandler::readHumidity(){
  if(nullptr != getDataProvider() ){
    getDataProvider()->setCurrentHumidityLvl(analogRead(m_operatedPin));
  }
};

 void HumidityHandler::cyclic() {
  Serial.println("HumidityHandler - Cyclic Task");
  readHumidity();
};