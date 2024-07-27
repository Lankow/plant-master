/**
 * @file DisplayRenderer.hpp
 * @date 2024-05-26
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

#include <memory>
#include <string>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include "config/Constants.hpp"
#include "config/Configurator.hpp"

#include <memory>
#include <string>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include "config/Constants.hpp"
#include "config/Configurator.hpp"

class DisplayRenderer
{
public:
    explicit DisplayRenderer(std::shared_ptr<Configurator> configurator);

    void init();
    void displayScreen(Screen::Type screenToDisplay);

private:
    Adafruit_SSD1306 m_display;
    int16_t m_currentLine;
    bool m_isInitialized;

    void initializeDisplay();
    void resetDisplay();
    void drawHeading(const std::string &text);
    void drawTextLine(const std::string &text);
    void drawInitialScreen();
    void drawAppScreen();
    void drawHelpScreen();
    void drawConfigScreen();
    void drawErrorScreen();
    void drawResetScreen();
};

#endif // DISPLAY_RENDERER_HPP
