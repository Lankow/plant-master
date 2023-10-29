/*
 *   HumidityData.cpp
 *   ----------------------
 *   Created on: 2023/10/29
 *   Author: Lankow
 */
#include "HumidityData.hpp"
#include "constants.hpp"

uint16_t HumidityData::getCurrentHumidityLvl()
{
  return m_currentHumidityLvl;
};

uint16_t HumidityData::getHumidityThreshold()
{
  return m_humidityThreshold;
};

bool HumidityData::getHumidityActive()
{
  return m_humidityActive;
};

void HumidityData::setCurrentHumidityLvl(uint16_t p_readHumidity)
{
  m_currentHumidityLvl = p_readHumidity;
};

void HumidityData::setHumidityThreshold(uint16_t p_newThreshold)
{
  m_humidityThreshold = p_newThreshold;
};

void HumidityData::setHumidityActive(bool p_humidityState)
{
  m_humidityActive = p_humidityState;
};
