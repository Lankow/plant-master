/*
 *   HumidityHandler.hpp
 *   ----------------------
 *   Created on: 2023/09/26
 *   Author: Lankow
 */
#ifndef HUMIDITY_HANDLER_HPP
#define HUMIDITY_HANDLER_HPP

#include "Component.hpp"

class HumidityHandler : public Component
{
public:
    HumidityHandler(uint8_t pin);

    void handleHumidity();
    void init() override;
    void cyclic() override;

private:
    uint8_t m_operatedPin;
    uint8_t m_handlerId;
};

#endif // HUMIDITY_HANDLER_HPP
