/**
 * @file DisplayRenderer.hpp
 * @date   2024-05-26
 * @author Lankow
 * @version 1.0
 *
 * @brief This file contains the definition of the DisplayRenderer class.
 *
 * The DisplayRenderer class is responsible for rendering various screens on an OLED display,
 * including the initial screen, configuration screen, and connected screen.
 */
#ifndef DISPLAY_RENDERER_HPP
#define DISPLAY_RENDERER_HPP

#include <Wire.h>
#include <SSD1306Wire.h>
#include "config/Constants.hpp"

/**
 * @class DisplayRenderer
 * @brief A class for rendering various screens on an OLED display.
 *
 * The DisplayRenderer class handles initializing the display and drawing different screens
 * such as the initial screen, configuration screen, and connected screen.
 */
class DisplayRenderer
{
public:
    /**
     * @brief Constructs a new DisplayRenderer object.
     */
    DisplayRenderer();

    /**
     * @brief Draws the initial screen.
     *
     * This method displays the initial screen with the application name and a line separator.
     */
    void drawInitialScreen();

    /**
     * @brief Draws the configuration screen.
     *
     * This method displays the configuration screen showing the provided SSID and password.
     *
     * @param ssid The SSID to display.
     * @param password The password to display.
     */
    void drawConfigScreen(const std::string &ssid, const std::string &password);

    /**
     * @brief Draws the connected screen.
     *
     * This method displays the connected screen showing the provided IP address.
     *
     * @param ip The IP address to display.
     */
    void drawConnectedScreen(const std::string &ip);

private:
    SSD1306Wire m_display; /**< OLED display instance. */

    static const int I2C_ADDRESS = 0x3C;        /**< I2C address of the OLED display. */
    static const int DISPLAY_WIDTH = 128;       /**< Width of the OLED display in pixels. */
    static const int DISPLAY_HEIGHT = 64;       /**< Height of the OLED display in pixels. */
    static const int TEXT_X_POS = 10;           /**< X position for text rendering. */
    static const int TEXT_Y_POS_INITIAL = 10;   /**< Y position for text on the initial screen. */
    static const int TEXT_Y_POS_CONNECTED = 12; /**< Y position for text on the connected screen. */
    static const int LINE_Y_POS_INITIAL = 26;   /**< Y position for the line on the initial screen. */
    static const int LINE_Y_POS_CONNECTED = 10; /**< Y position for the line on the connected screen. */
    static const int LINE_LENGTH = 100;         /**< Length of the horizontal line in pixels. */

    /**
     * @brief Initializes the display.
     *
     * This method sets up the OLED display.
     */
    void initializeDisplay();
};

#endif // DISPLAY_RENDERER_HPP