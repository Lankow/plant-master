/*
*   HumidityHandler.cpp
*   ----------------------
*   Created on: 2023/09/26
*   Author: Lankow
*/
#include <Arduino.h>

#include "HumidityHandler.h"
#include "constants.h"

    HumidityHandler::HumidityHandler(int pin, int threshold):
                                     m_operatedPin(pin),
                                     m_humidityThreshold(threshold),
                                     m_currentHumidityLvl(ANALOG_PIN_MAX),
                                     m_needsWatering(false)
    {};
    
    void HumidityHandler::readHumidity(){
      if(NULL != &m_operatedPin ){
        m_currentHumidityLvl = analogRead(m_operatedPin);
        compareHumidity();
      }
    };

    void HumidityHandler::compareHumidity(){
      pinMode(LED_BUILTIN, OUTPUT);
      if(m_currentHumidityLvl <= m_humidityThreshold){
        m_needsWatering = true;
        digitalWrite(LED_BUILTIN, HIGH);
        }
      else{
        m_needsWatering = false;
        digitalWrite(LED_BUILTIN, LOW);
        }
    }

    void HumidityHandler::setHumidityThreshold(int threshold){
      if(NULL != &threshold){
        m_humidityThreshold = threshold;
      }
    };

    void HumidityHandler::setOperatedPin(int pin){
      if(NULL != &pin){
        m_operatedPin = pin;
      }
    };

    bool HumidityHandler::getNeedsWatering(){
      return m_needsWatering;
    };
