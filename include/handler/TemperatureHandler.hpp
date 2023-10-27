/*
 *   TemperatureHandler.hpp
 *   ----------------------
 *   Created on: 2023/10/01
 *   Author: Lankow
 */
#ifndef TEMPERATURE_HANDLER_HPP
#define TEMPERATURE_HANDLER_HPP

#include <DHT.h>
#include "Component.hpp"

class TemperatureHandler : public Component
{
public:
  TemperatureHandler(int pin);

  void cyclic();

private:
  DHT m_dht;

  void handleTemperature();
  void handleRoomHumidity();
};
#endif // TEMPERATURE_HANDLER_HPP