/**
 * @file DisplayRenderer.cpp
 * @date 2024-05-26
 * @author Lankow
 * @version 1.0
 *
 * @brief This file contains the implementation of the DisplayRenderer class.
 *
 * The DisplayRenderer class is responsible for rendering various screens on an OLED display,
 * including the initial screen, configuration screen, and connected screen.
 */

#include <Adafruit_GFX.h>
#include <SPI.h>
#include "utilities/DisplayRenderer.hpp"

DisplayRenderer::DisplayRenderer(std::shared_ptr<Configurator> configurator)
    : m_display(Screen::WIDTH, Screen::HEIGHT, &SPI, configurator->getOledDcPin(),
                configurator->getOledResetPin(), configurator->getOledCsPin()),
      m_isInitialized(false),
      m_screenTimeCounter(0),
      m_currentLine(0)
{
    m_isInitialized = initializeDisplay();
    displayScreen(Screen::Type::InitialScreen);
}

void DisplayRenderer::cyclic()
{
    m_screenTimeCounter -= Config::CYCLE_TIME_MS;
}

void DisplayRenderer::displayScreen(Screen::Type screenToDisplay)
{
    if (!m_isInitialized || m_screenTimeCounter > 0)
    {
        return;
    }

    resetDisplay();

    switch (screenToDisplay)
    {
    case Screen::Type::InitialScreen:
        drawInitialScreen();
        break;
    case Screen::Type::AppScreen:
        drawAppScreen();
        break;
    case Screen::Type::HelpScreen:
        drawHelpScreen();
        break;
    case Screen::Type::ConfigScreen:
        drawConfigScreen();
        break;
    case Screen::Type::ErrorScreen:
        drawErrorScreen();
        break;
    case Screen::Type::ResetScreen:
        drawResetScreen();
        return;
    }
    m_display.display();
}

bool DisplayRenderer::initializeDisplay()
{
    if (!m_display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    {
        m_display.println(F("SSD1306 allocation failed"));
        return false;
    }

    return true;
}

void DisplayRenderer::drawHeading(const std::string &text)
{
    m_display.setTextSize(Screen::TEXT_SIZE);
    m_display.setTextColor(SSD1306_WHITE);
    m_display.setCursor(Screen::HEADING_X, Screen::HEADING_Y);
    m_display.print(text.c_str());
    m_display.drawLine(Screen::HEADING_X, Screen::HEADING_LINE_Y,
                       Screen::WIDTH, Screen::HEADING_LINE_Y, SSD1306_WHITE);
}

void DisplayRenderer::drawTextLine(const std::string &text)
{
    int16_t yPosition = Screen::TEXT_Y + (m_currentLine * 10);

    if (yPosition < Screen::HEIGHT)
    {
        m_display.setTextSize(Screen::TEXT_SIZE);
        m_display.setTextColor(SSD1306_WHITE);
        m_display.setCursor(Screen::TEXT_X, yPosition);
        m_display.print(text.c_str());
        ++m_currentLine;
    }
}

void DisplayRenderer::resetDisplay()
{
    m_display.clearDisplay();
    m_currentLine = 0;
}

void DisplayRenderer::drawInitialScreen()
{
    drawHeading("Plant-Master");
    drawTextLine("App by Lankow");
}

void DisplayRenderer::drawAppScreen()
{
    drawHeading("Plant-Master App");
    drawTextLine("Application address:");
    drawTextLine(Network::IP::LOCAL.toString().c_str());
}

void DisplayRenderer::drawHelpScreen()
{
    drawHeading("Plant-Master Help");
    drawTextLine("Hold boot button to reset device settings.Use Plant-Master web app to update config.");
    m_screenTimeCounter = Screen::SCREEN_DURATION;
}

void DisplayRenderer::drawConfigScreen()
{
    drawHeading("Plant-Master Config");
    drawTextLine("SSID: " + Config::PAGE_SSID);
    drawTextLine("Password: " + Config::PAGE_PASSWORD);
}

void DisplayRenderer::drawErrorScreen()
{
    drawHeading("Plant-Master Error");
    drawTextLine("Plant master encountered an error. See logs for more information.");
    m_screenTimeCounter = Screen::SCREEN_DURATION;
}

void DisplayRenderer::drawResetScreen()
{
    for (int i = 3; i >= 0; --i)
    {
        resetDisplay();
        drawHeading("Plant-Master Reset");
        drawTextLine("Reset in " + std::to_string(i) + " seconds...");
        m_display.display();
        delay(1000);
    }
}