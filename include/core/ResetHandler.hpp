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

/**
 * @class ResetHandler
 * @brief A class for handling reset button events and performing system resets.
 *
 * The ResetHandler class checks the state of a reset button and performs a system reset if the
 * button is pressed for a specified duration.
 */
class ResetHandler
{
public:
    /**
     * @brief Constructs a new ResetHandler object.
     */
    ResetHandler();

    /**
     * @brief Initializes the reset button.
     *
     * This method should be called to initialize the reset button before using it.
     */
    void init();

    /**
     * @brief Checks the reset button state and performs actions based on its state.
     *
     * This method should be called cyclically to ensure that the reset button state is checked
     * and actions are taken accordingly.
     */
    void cyclic();

private:
    uint16_t m_pressedCounter; /**< Counter to track the duration the reset button has been pressed. */
    Button m_resetButton;      /**< The reset button object. */
    bool m_resetButtonPressed; /**< Flag to indicate if the reset button is currently pressed. */

    /**
     * @brief Performs a system reset.
     *
     * This method clears preferences and restarts the system.
     */
    void performReset();
};

#endif // RESET_HANDLER_HPP