/*
 *   PumpHandler.hpp
 *   ----------------------
 *   Created on: 2023/10/01
 *   Author: Lankow
 */
#ifndef PUMP_HANDLER_HPP
#define PUMP_HANDLER_HPP

#include "Component.hpp"

class PumpHandler : public Component
{
public:
  PumpHandler(const uint8_t pin);

  void init() override;
  void cyclic() override;

private:
  void handlePump();
  const uint8_t m_operatedPin;
};
#endif // PUMP_HANDLER_HPP