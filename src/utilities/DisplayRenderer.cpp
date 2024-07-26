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

#include "utilities/DisplayRenderer.hpp"
#include <Adafruit_GFX.h>
#include <SPI.h>

Screen::Type DisplayRenderer::displayedScreen = Screen::Type::None;

DisplayRenderer::DisplayRenderer(std::shared_ptr<Configurator> configurator)
    : m_display(Screen::WIDTH, Screen::HEIGHT, &SPI, configurator->getOledDcPin(),
                configurator->getOledResetPin(), configurator->getOledCsPin()),
      m_isInitialized(false),
      m_currentLine(0)
{
}

void DisplayRenderer::displayScreen(Screen::Type screenToDisplay)
{
    displayedScreen = screenToDisplay;
}

void DisplayRenderer::init()
{
    initializeDisplay();
    displayScreen(Screen::Type::InitialScreen);
}

void DisplayRenderer::cyclic()
{
    if (m_isInitialized)
    {
        switch (displayedScreen)
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
        case Screen::Type::ResetScreen:
            drawResetScreen();
            break;
        case Screen::Type::None:
        default:
            resetDisplay();
        }
    }
}

void DisplayRenderer::initializeDisplay()
{
    if (!m_display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    {
        m_display.println(F("SSD1306 allocation failed"));
        return;
    }

    m_isInitialized = true;
}

void DisplayRenderer::drawInitialScreen()
{
    resetDisplay();
    drawHeading("Plant-Master");
    drawTextLine("App by Lankow");
    m_display.display();
    delay(Screen::INITIAL_DURATION);
}

void DisplayRenderer::drawConfigScreen()
{
    resetDisplay();
    drawHeading("Plant-Master Config");
    drawTextLine("SSID: " + Config::PAGE_SSID);
    drawTextLine("Password: " + Config::PAGE_PASSWORD);
    m_display.display();
    delay(Screen::INITIAL_DURATION);
}

void DisplayRenderer::drawAppScreen()
{
    resetDisplay();
    drawHeading("Plant-Master App");
    drawTextLine("Application address:");
    drawTextLine(Network::IP::LOCAL.toString().c_str());
    m_display.display();
    delay(Screen::INITIAL_DURATION);
}

void DisplayRenderer::drawHelpScreen()
{
    resetDisplay();
    drawHeading("Plant-Master Help");
    m_display.display();
    delay(Screen::INITIAL_DURATION);
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

void DisplayRenderer::drawErrorScreen()
{
    resetDisplay();
    drawHeading("Plant-Master Error");
    drawTextLine("Error: ");
    m_display.display();
    delay(Screen::INITIAL_DURATION);
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
    m_display.display();
}
