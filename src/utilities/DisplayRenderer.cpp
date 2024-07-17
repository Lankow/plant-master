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
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <SPI.h>

DisplayRenderer::DisplayRenderer(std::shared_ptr<Configurator> configurator)
    : m_display(Screen::SCREEN_WIDTH, Screen::SCREEN_HEIGHT, &SPI, configurator->getOledDcPin(), configurator->getOledResetPin(), configurator->getOledCsPin())
{
    initializeDisplay();
}

void DisplayRenderer::initializeDisplay()
{
    if (!m_display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    {
        m_display.println(F("SSD1306 allocation failed"));
        return;
    }

    m_display.clearDisplay();

    m_display.fillRect(0, 0, 128, 64, SSD1306_WHITE);
    m_display.setCursor(0, 0);
    m_display.setTextColor(SSD1306_BLACK);
    m_display.setTextSize(1);
    m_display.println("Plant-Master");

    m_display.display();
}

void DisplayRenderer::drawInitialScreen()
{
    delay(Screen::INITIAL_SCREEN_DURATION);
}
