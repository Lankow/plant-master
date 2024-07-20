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

    m_display.fillRect(0, 0, 128, 64, SSD1306_WHITE);
    m_display.setCursor(0, 0);
    m_display.setTextColor(SSD1306_BLACK);
    m_display.setTextSize(1);
    m_display.println("Plant-Master");

    m_display.display();
}

void DisplayRenderer::drawInitialScreen()
{
    m_display.clearDisplay();

    const char *line1 = "Plant Master";
    const char *line2 = "by Lankow";

    int16_t x1, y1;
    uint16_t textWidth1, textHeight1;
    m_display.getTextBounds(line1, 0, 0, &x1, &y1, &textWidth1, &textHeight1);

    uint16_t textWidth2, textHeight2;
    m_display.getTextBounds(line2, 0, 0, &x1, &y1, &textWidth2, &textHeight2);

    int16_t xOffset1 = (Screen::WIDTH - textWidth1) / 2;
    int16_t yOffset1 = (Screen::HEIGHT / 2) - textHeight1;

    int16_t xOffset2 = (Screen::WIDTH - textWidth2) / 2;
    int16_t yOffset2 = (Screen::HEIGHT / 2) + 2;

    m_display.setTextSize(1);
    m_display.setTextColor(SSD1306_WHITE);

    m_display.setCursor(xOffset1, yOffset1);
    m_display.print(line1);

    m_display.setCursor(xOffset2, yOffset2);
    m_display.print(line2);

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

void DisplayRenderer::resetDisplay()
{
    m_offsetX = Screen::DEFAULT_OFFSET_X;
    m_offsetY = Screen::DEFAULT_OFFSET_Y;
    m_display.setCursor(m_offsetX, m_offsetY);

    m_display.clearDisplay();
}

void DisplayRenderer::displayText(std::string text)
{
    // Calculate size of the text
    // Split text into lines
    // display lines
}