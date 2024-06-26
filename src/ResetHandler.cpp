/*
 *   ResetHandler.cpp
 *   ----------------------
 *   Created on: 2024/06/12
 *   Author: Lankow
 */
#include <Preferences.h>
#include "ResetHandler.hpp"
#include "Constants.hpp"

ResetHandler::ResetHandler()
    : m_pressedCounter(ResetButton::DEFAULT_TIME),
      m_resetButton(ResetButton::PIN),
      m_resetButtonPressed(false){};

void ResetHandler::init()
{
    m_resetButton.begin();
}

void ResetHandler::cyclic()
{
    if (m_pressedCounter > ResetButton::THRESHOLD_TIME_MS)
    {
        Serial.println("Performing reset for target..");
        // performReset();
    }

    if (m_resetButton.pressed())
    {
        Serial.println("Reset button pressed...");
        m_resetButtonPressed = true;
    }

    if (m_resetButton.released())
    {
        Serial.println("Reset button released...");
        m_resetButtonPressed = false;
    }

    if (m_resetButtonPressed)
    {
        m_pressedCounter += Config::CYCLE_TIME_MS;
    }
    else
    {
        m_pressedCounter = ResetButton::DEFAULT_TIME;
    }
}

void ResetHandler::performReset()
{
    Preferences preferences;
    if (!preferences.begin("wifi-config", false))
    {
        Serial.println("Failed to open NVS namespace.");
        return;
    }

    Serial.println("Performing Plant-Master reset...");
    preferences.clear();
    preferences.end();

    delay(100);
    ESP.restart();
}