/*
 *   HumidityData.cpp
 *   ----------------------
 *   Created on: 2023/10/29
 *   Author: Lankow
 */
#include "HumidityData.hpp"
#include "constants.hpp"

uint16_t HumidityData::getCurrentHumidityLvl() const
{
  return m_currentHumidityLvl;
};

uint16_t HumidityData::getHumidityThreshold() const
{
  return m_humidityThreshold;
};

bool HumidityData::getHumidityActive() const
{
  return m_humidityActive;
};

void HumidityData::setCurrentHumidityLvl(const uint16_t readHumidity)
{
  m_currentHumidityLvl = readHumidity;
};

void HumidityData::setHumidityThreshold(const uint16_t newThreshold)
{
  m_humidityThreshold = newThreshold;
};

void HumidityData::setHumidityActive(const bool humidityState)
{
  m_humidityActive = humidityState;
};
