/*
 *   DisplayRenderer.hpp
 *   ----------------------
 *   Created on: 2024/05/26
 *   Author: Lankow
 */
#ifndef DISPLAY_RENDERER_HPP
#define DISPLAY_RENDERER_HPP

#include <Wire.h>
#include <SSD1306Wire.h>
#include "Constants.hpp"

class DisplayRenderer
{
public:
    DisplayRenderer();

    void drawInitialScreen();
    void drawConfigScreen(const std::string &ssid, const std::string &password);
    void drawConnectedScreen(const std::string &ip);

private:
    void initializeDisplay();

    SSD1306Wire m_display;

    static const int I2C_ADDRESS = 0x3C;
    static const int DISPLAY_WIDTH = 128;
    static const int DISPLAY_HEIGHT = 64;
    static const int TEXT_X_POS = 10;
    static const int TEXT_Y_POS_INITIAL = 10;
    static const int TEXT_Y_POS_CONNECTED = 12;
    static const int LINE_Y_POS_INITIAL = 26;
    static const int LINE_Y_POS_CONNECTED = 10;
    static const int LINE_LENGTH = 100;
};

#endif // DISPLAY_RENDERER_HPP