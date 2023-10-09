/*
*   TemperatureHandler.hpp
*   ----------------------
*   Created on: 2023/10/01
*   Author: Lankow
*/
#ifndef TEMPERATURE_HANDLER_HPP
#define TEMPERATURE_HANDLER_HPP

#include <DHT.h>
#include "Handler.hpp"

class TemperatureHandler : public Handler{
  private:
  DHT m_dht;

  void readTemperature();
  void readRoomHumidity();

  public:
  TemperatureHandler(int pin);

  void cyclic();

};
#endif // TEMPERATURE_HANDLER_HPP