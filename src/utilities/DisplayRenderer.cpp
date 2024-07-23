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
    : m_display(Screen::WIDTH, Screen::HEIGHT, &SPI, configurator->getOledDcPin(), configurator->getOledResetPin(), configurator->getOledCsPin()),
      m_isInitialized(false)
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

    m_isInitialized = true;
    drawInitialScreen();
}

void DisplayRenderer::drawInitialScreen()
{
    if (m_isInitialized)
    {
        resetDisplay();
        drawHeading("Plant-Master");
        drawTextLine("App by Lankow");
        m_display.display();

        delay(3000);
    }
}

void DisplayRenderer::drawAccessPointScreen()
{
    if (m_isInitialized)
    {
        resetDisplay();
        drawHeading("Plant-Master Config");
        drawTextLine("SSID: ");
        drawTextLine(Config::PAGE_SSID);
        drawTextLine("Password:");
        drawTextLine(Config::PAGE_PASSWORD);
        m_display.display();

        delay(3000);
    }
};

void DisplayRenderer::drawWebSocketScreen()
{
    if (m_isInitialized)
    {
        resetDisplay();
        drawHeading("Plant-Master App");
        drawTextLine("Application address:");
        drawTextLine(Network::IP::LOCAL.toString().c_str());
        m_display.display();

        delay(3000);
    }
};

void DisplayRenderer::drawHelpScreen()
{
    if (m_isInitialized)
    {
        resetDisplay();
        drawHeading("Plant-Master Help");
        m_display.display();

        delay(3000);
    }
};

void DisplayRenderer::drawResetScreen()
{
    if (m_isInitialized)
    {
        for (int i = 3; i >= 0; i--)
        {
            resetDisplay();
            drawHeading("Plant-Master Reset");
            drawTextLine("Reset in " + std::to_string(i) + " seconds...");
            m_display.display();

            delay(1000);
        }
    }
};

void DisplayRenderer::drawHeading(std::string text)
{
    m_display.setTextSize(1);
    m_display.setTextColor(SSD1306_WHITE);

    m_display.setCursor(Screen::DEFAULT_HEADING_OFFSET_X, Screen::DEFAULT_HEADING_OFFSET_Y);
    m_display.print(text.c_str());
    m_display.drawLine(Screen::DEFAULT_HEADING_OFFSET_X, Screen::DEFAULT_HEADING_LINE_OFFSET_Y, Screen::WIDTH, Screen::DEFAULT_HEADING_LINE_OFFSET_Y, SSD1306_WHITE);
}

void DisplayRenderer::drawTextLine(std::string text)
{
    m_display.setTextSize(1);
    m_display.setTextColor(SSD1306_WHITE);

    m_display.setCursor(0, 16 + (m_currentLine++ * 10));
    m_display.print(text.c_str());
}

void DisplayRenderer::resetDisplay()
{
    m_display.clearDisplay();
    m_currentLine = 0;
    m_display.display();
}