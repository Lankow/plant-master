/*
 *   ValveHandler.hpp
 *   ----------------------
 *   Created on: 2023/10/01
 *   Author: Lankow
 */
#ifndef VALVE_HANDLER_HPP
#define VALVE_HANDLER_HPP

#include "Component.hpp"

class ValveHandler : public Component
{

public:
  void handleValves();
  void cyclic();
};
#endif // VALVE_HANDLER_HPP