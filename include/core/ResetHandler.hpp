/**
 * @file ResetHandler.hpp
 * @date   2024-06-12
 * @author Lankow
 * @version 1.0
 *
 * @brief This file contains the definition of the ResetHandler class.
 *
 * The ResetHandler class is responsible for handling the reset button press event and performing
 * a system reset if the button is pressed for a specified duration.
 */
#ifndef RESET_HANDLER_HPP
#define RESET_HANDLER_HPP

#include <Arduino.h>
#include <Button.h>
#include <memory>
#include <utilities/DisplayRenderer.hpp>

class ResetHandler
{
public:
    ResetHandler();
    ResetHandler(std::shared_ptr<DisplayRenderer> displayRenderer);

    void init();
    void cyclic();

private:
    std::shared_ptr<DisplayRenderer> m_displayRenderer;
    uint16_t m_pressedCounter;
    Button m_resetButton;
    bool m_resetButtonPressed;

    void performReset();
};

#endif // RESET_HANDLER_HPP