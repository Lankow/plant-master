/*
 *   DisplayRenderer.hpp
 *   ----------------------
 *   Created on: 2024/05/26
 *   Author: Lankow
 */
#ifndef DISPLAY_RENDERER_HPP
#define DISPLAY_RENDERER_HPP

#include <Wire.h>  
#include "SSD1306Wire.h"
#include "OLEDDisplayUi.h"

class DisplayRenderer
{
    public:
    DisplayRenderer();

    void drawInitialScreen();
    void drawConfigScreen(std::string ssid, std::string password);
    void drawConnectedScreen(std::string ip);

    private:
    SSD1306Wire m_display;
};

#endif // DISPLAY_RENDERER_HPP