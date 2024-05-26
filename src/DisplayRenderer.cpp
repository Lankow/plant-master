/*
 *   DisplayRenderer.cpp
 *   ----------------------
 *   Created on: 2024/05/26
 *   Author: Lankow
 */
#include "DisplayRenderer.hpp"
#include "Constants.hpp"

DisplayRenderer::DisplayRenderer(): m_display(0x03, SDA, SCL){};

void DisplayRenderer::drawInitialScreen(){
    m_display.clear();
    m_display.drawString(30, 10, "Plant-Master");
    m_display.drawHorizontalLine(10, 26, 100);
    m_display.drawString(35, 30, "by Lankow");
    m_display.display();

    delay(INITIAL_SCREEN_DURATION);
}

void DisplayRenderer::drawConfigScreen(String ssid, String password){
    m_display.clear();
    m_display.drawString(10, 0, "Config SSID:");
    m_display.drawString(10, 10, ssid);
    m_display.drawHorizontalLine(10, 24, 100);
    m_display.drawString(10, 25, "Config PASSWORD:");
    m_display.drawString(10, 35, password);
    m_display.display();
}