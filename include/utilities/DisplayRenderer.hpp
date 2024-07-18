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
#include <Adafruit_SSD1306.h>
#include "config/Constants.hpp"
#include "config/Configurator.hpp"
class DisplayRenderer
{
public:
    DisplayRenderer(std::shared_ptr<Configurator> configurator);

    void drawInitialScreen();
    void drawAccessPointScreen();
    void drawWebSocketScreen();
    void drawHumidityScreen();
    void drawResetScreen();

private:
    Adafruit_SSD1306 m_display;

    void initializeDisplay();
};

#endif // DISPLAY_RENDERER_HPP