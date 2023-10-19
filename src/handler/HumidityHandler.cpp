/*
*   HumidityHandler.cpp
*   ----------------------
*   Created on: 2023/09/26
*   Author: Lankow
*/
#include "handler/HumidityHandler.hpp"
#include "constants.hpp"
#include "Logger.hpp"

static uint8_t m_idCounter;

HumidityHandler::HumidityHandler(uint8_t p_operatedPin):
                                 m_operatedPin(p_operatedPin){
                                  m_handlerId = m_idCounter;
                                  m_idCounter++;
                                 };

void HumidityHandler::handleHumidity(){
  if(nullptr != getDataProvider() ){
    uint16_t result = analogRead(m_operatedPin);

    if(result != ANALOG_PIN_MAX){
      getDataProvider()->setCurrentHumidityLvl(m_handlerId, result);
      getDataProvider()->setHumidityActive(m_handlerId, true);
    }else{
      getDataProvider()->setHumidityActive(m_handlerId, false);    
    }

  }
};

 void HumidityHandler::cyclic() {
  getLogger()->log(Logger::INFO, "HumidityHandler - Cyclic Task");
  handleHumidity();
};