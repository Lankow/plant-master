/**
 * @file ResetHandler.cpp
 * @date   2024-06-12
 * @author Lankow
 * @version 1.0
 *
 * @brief This file contains the implementation of the ResetHandler class.
 *
 * The ResetHandler class is responsible for handling the reset button press event and performing
 * a system reset if the button is pressed for a specified duration.
 */

#include <Preferences.h>
#include "core/ResetHandler.hpp"
#include "config/Constants.hpp"
#include "utilities/DisplayRenderer.hpp"

ResetHandler::ResetHandler()
    : m_pressedCounter(ResetButton::DEFAULT_TIME),
      m_resetButton(ResetButton::PIN),
      m_resetButtonPressed(false),
      m_displayRenderer(nullptr),
      m_lastPressTime(0),
      m_doubleClickDetected(false) {}

ResetHandler::ResetHandler(std::shared_ptr<DisplayRenderer> displayRenderer)
    : m_pressedCounter(ResetButton::DEFAULT_TIME),
      m_resetButton(ResetButton::PIN),
      m_resetButtonPressed(false),
      m_displayRenderer(displayRenderer),
      m_lastPressTime(0),
      m_doubleClickDetected(false) {}

void ResetHandler::init()
{
    m_resetButton.begin();
}

void ResetHandler::cyclic()
{
    unsigned long currentTime = millis();

    if (m_resetButton.pressed())
    {
        Serial.println("Reset button pressed...");
        m_resetButtonPressed = true;

        if (currentTime - m_lastPressTime < ResetButton::DOUBLE_CLICK_THRESHOLD_MS)
        {
            m_doubleClickDetected = true;
            onDoubleClick();
        }

        m_lastPressTime = currentTime;
    }

    if (m_resetButton.released())
    {
        Serial.println("Reset button released...");
        m_resetButtonPressed = false;
        m_pressedCounter = ResetButton::DEFAULT_TIME;
    }

    if (m_resetButtonPressed)
    {
        m_pressedCounter += Config::CYCLE_TIME_MS;

        if (m_pressedCounter > ResetButton::THRESHOLD_TIME_MS)
        {
            Serial.println("Performing reset for target..");
            m_displayRenderer->displayScreen(Screen::Type::ResetScreen);
            performReset();
        }
    }

    if (m_doubleClickDetected)
    {
        m_doubleClickDetected = false;
    }
}

void ResetHandler::performReset()
{
    Preferences preferences;
    if (!preferences.begin("wifi-config", false))
    {
        m_displayRenderer->displayScreen(Screen::Type::ErrorScreen);
        Serial.println("Failed to open NVS namespace.");
        return;
    }

    Serial.println("Performing Plant-Master reset...");
    preferences.clear();
    preferences.end();

    delay(100);
    ESP.restart();
}

void ResetHandler::onDoubleClick()
{
    m_displayRenderer->displayScreen(Screen::Type::HelpScreen);
}