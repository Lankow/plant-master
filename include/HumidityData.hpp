/*
 *   HumidityData.hpp
 *   ----------------------
 *   Created on: 2023/10/29
 *   Author: Lankow
 */
#ifndef HUMIDITY_DATA_HPP
#define HUMIDITY_DATA_HPP

#include <Arduino.h>
#include "constants.hpp"

class HumidityData
{
public:
  uint16_t getCurrentHumidityLvl() const;
  uint16_t getHumidityThreshold() const;
  bool getHumidityActive() const;

  void setCurrentHumidityLvl(const uint16_t readHumidity);
  void setHumidityThreshold(const uint16_t newThreshold);
  void setHumidityActive(const bool humidityState);

private:
  uint16_t m_currentHumidityLvl = DEFAULT_HUMIDITY_LVL;
  uint16_t m_humidityThreshold = DEFAULT_THRESHOLD;
  bool m_humidityActive = DEFAULT_ACTIVE;
};
#endif // HUMIDITY_DATA_HPP