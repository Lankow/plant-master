/*
 *   ValveController.hpp
 *   ----------------------
 *   Created on: 2024/05/29
 *   Author: Lankow
 */
#ifndef VALVE_CONTROLLER_HPP
#define VALVE_CONTROLLER_HPP

#include <Arduino.h>
#include <memory>
#include "Configurator.hpp"

class ValveController
{
public:
    ValveController(std::shared_ptr<Configurator> configurator);

    void turnOn();
    void turnOff();

private:
    std::shared_ptr<Configurator> m_configurator;
};

#endif // VALVE_CONTROLLER_HPP