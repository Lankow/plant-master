/*
 *   ValveController.cpp
 *   ----------------------
 *   Created on: 2024/05/29
 *   Author: Lankow
 */

#include "ValveController.hpp"

ValveController::ValveController(std::shared_ptr<Configurator> configurator)
    : m_configurator(configurator){};

void ValveController::turnOn() {};

void ValveController::turnOff() {};
