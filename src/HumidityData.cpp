/*
*   HumidityData.hpp
*   ----------------------
*   Created on: 2023/10/09
*   Author: Lankow
*/
#include "HumidityData.hpp"

HumidityData::HumidityData(): m_currentHumidityLvl(0),
                              m_humidityThreshold(4095),
                              m_needsWatering(false),
                              m_isActive(false){};

int& HumidityData::getCurrentHumidityLvl(){ 
  return m_currentHumidityLvl;
};

int& HumidityData::getHumidityThreshold(){ 
return m_humidityThreshold; 
};

bool& HumidityData::getNeedsWatering(){ 
return m_needsWatering; 
};

bool& HumidityData::getIsActive(){ 
return m_isActive; 
};

void HumidityData::setCurrentHumidityLvl(int p_currentHumidityLvl){
  if(nullptr != &p_currentHumidityLvl){
    m_currentHumidityLvl = p_currentHumidityLvl;
  }
};

void HumidityData::setHumidityThreshold(int p_humidityThreshold){
  if(nullptr != &p_humidityThreshold){
    m_humidityThreshold = p_humidityThreshold;
  }
};

void HumidityData::setNeedsWatering(bool p_needsWatering){
  if(nullptr != &p_needsWatering){
    m_needsWatering = p_needsWatering;
  }
};

void HumidityData::setIsActive(bool p_isActive){
  if(nullptr != &p_isActive){
    m_isActive = p_isActive;
  }
};