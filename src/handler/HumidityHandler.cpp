/*
*   HumidityHandler.cpp
*   ----------------------
*   Created on: 2023/09/26
*   Author: Lankow
*/
#include "handler/HumidityHandler.hpp"
#include "constants.hpp"

static uint8_t m_idCounter;

HumidityHandler::HumidityHandler(uint8_t p_operatedPin):
                                 m_operatedPin(p_operatedPin){
                                  m_handlerId = m_idCounter;
                                  m_idCounter++;
                                 };

void HumidityHandler::handleHumidity(){
  if(nullptr != getDataProvider() ){
    getDataProvider()->setCurrentHumidityLvl(m_handlerId, analogRead(m_operatedPin));
  }
};

 void HumidityHandler::cyclic() {
  Logger::log("HumidityHandler - Cyclic Task");
  handleHumidity();
};