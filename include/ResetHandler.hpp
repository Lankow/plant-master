/*
 *   ResetHandler.hpp
 *   ----------------------
 *   Created on: 2024/06/12
 *   Author: Lankow
 */
#ifndef RESET_HANDLER_HPP
#define RESET_HANDLER_HPP

#include <Arduino.h>
#include <Button.h>

class ResetHandler
{
public:
    ResetHandler();

    void init();
    void cyclic();

private:
    uint16_t m_pressedCounter;
    Button m_resetButton;
    bool m_resetButtonPressed;

    void performReset();
};

#endif // RESET_HANDLER_HPP