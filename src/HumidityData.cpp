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

void HumidityData::setCurrentHumidityLvl(uint16_t readHumidity)
{
  m_currentHumidityLvl = readHumidity;
};

void HumidityData::setHumidityThreshold(uint16_t newThreshold)
{
  m_humidityThreshold = newThreshold;
};

void HumidityData::setHumidityActive(bool humidityState)
{
  m_humidityActive = humidityState;
};
