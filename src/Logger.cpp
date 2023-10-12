/*
*   Logger.cpp
*   ----------------------
*   Created on: 2023/10/09
*   Author: Lankow
*/
#include <Arduino.h>
#include "Logger.hpp"
#include "Component.hpp"

Logger::Logger(Component* p_sdCardHandler) : m_sdCardHandler(p_sdCardHandler) {};

void Logger::log(const char* message) {
    Serial.println(message);
    // Saving to SD card
}