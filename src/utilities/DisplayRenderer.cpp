/**
 * @file DisplayRenderer.cpp
 * @date   2024-05-26
 * @author Lankow
 * @version 1.0
 *
 * @brief This file contains the implementation of the DisplayRenderer class.
 *
 * The DisplayRenderer class is responsible for rendering various screens on an OLED display,
 * including the initial screen, configuration screen, and connected screen.
 */
#include "utilities/DisplayRenderer.hpp"

DisplayRenderer::DisplayRenderer()
    : m_display(I2C_ADDRESS, SDA, SCL)
{
    initializeDisplay();
}

void DisplayRenderer::initializeDisplay()
{
    m_display.init();
    m_display.clear();
    m_display.display();
}

void DisplayRenderer::drawInitialScreen()
{
    m_display.clear();
    m_display.drawString(TEXT_X_POS, TEXT_Y_POS_INITIAL, "Plant-Master");
    m_display.drawHorizontalLine(TEXT_X_POS, LINE_Y_POS_INITIAL, LINE_LENGTH);
    m_display.drawString(TEXT_X_POS + 25, TEXT_Y_POS_INITIAL + 20, "by XXX");
    m_display.display();

    delay(Screen::INITIAL_SCREEN_DURATION);
}

void DisplayRenderer::drawConfigScreen(const std::string &ssid, const std::string &password)
{
    m_display.clear();
    m_display.drawString(TEXT_X_POS, 0, "Config SSID:");
    m_display.drawString(TEXT_X_POS, TEXT_Y_POS_INITIAL, ssid.c_str());
    m_display.drawHorizontalLine(TEXT_X_POS, 24, LINE_LENGTH);
    m_display.drawString(TEXT_X_POS, 25, "Config PASSWORD:");
    m_display.drawString(TEXT_X_POS, 35, password.c_str());
    m_display.display();
}

void DisplayRenderer::drawConnectedScreen(const std::string &ip)
{
    m_display.clear();
    m_display.drawString(TEXT_X_POS, 0, "Plant-Master Server:");
    m_display.drawHorizontalLine(TEXT_X_POS, LINE_Y_POS_CONNECTED, LINE_LENGTH);
    m_display.drawString(TEXT_X_POS, TEXT_Y_POS_CONNECTED, ip.c_str());
    m_display.display();
}