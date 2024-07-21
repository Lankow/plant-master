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
    : m_display(Screen::WIDTH, Screen::HEIGHT, &SPI, configurator->getOledDcPin(), configurator->getOledResetPin(), configurator->getOledCsPin())
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
    m_display.display();
}

void DisplayRenderer::drawInitialScreen()
{
    m_display.clearDisplay();

    printHeading("Plant-Master");

    m_display.setCursor(0, 16);
    m_display.print("App by Lankow");

    m_display.display();

    delay(3000);
}

void DisplayRenderer::drawAccessPointScreen() {};

void DisplayRenderer::drawWebSocketScreen() {};

void DisplayRenderer::drawHumidityScreen() {};

void DisplayRenderer::drawResetScreen()
{
    int16_t xOffset = 0;
    int16_t yOffset = 7;

    for (int i = 3; i >= 0; i--)
    {
        m_display.clearDisplay();

        m_display.setTextSize(1);
        m_display.setTextColor(SSD1306_WHITE);

        m_display.setCursor(xOffset, yOffset);
        m_display.println("Device Reset in:");
        m_display.setCursor(xOffset, yOffset + 12);
        char countdownText[16];
        snprintf(countdownText, sizeof(countdownText), "%d seconds...", i);
        m_display.println(countdownText);

        m_display.display();

        delay(1000);
    }
};

void DisplayRenderer::printHeading(std::string text)
{
    m_display.setTextSize(1);
    m_display.setTextColor(SSD1306_WHITE);

    m_display.setCursor(Screen::DEFAULT_HEADING_OFFSET_X, Screen::DEFAULT_HEADING_OFFSET_Y);
    m_display.print("Plant Master");
    m_display.drawLine(Screen::DEFAULT_HEADING_OFFSET_X, Screen::DEFAULT_HEADING_LINE_OFFSET_Y, Screen::WIDTH, Screen::DEFAULT_HEADING_LINE_OFFSET_Y, SSD1306_WHITE);
}

void DisplayRenderer::printTextLine(std::string text)
{
}