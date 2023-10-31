/*
 *   Logger.cpp
 *   ----------------------
 *   Created on: 2023/10/09
 *   Author: Lankow
 */
#include <Arduino.h>
#include "Logger.hpp"

Logger::Logger(std::shared_ptr<SDCardHandler> sdCardHandler) : m_sdCardHandler(sdCardHandler) {}

String Logger::formatSysTime()
{
    long milliseconds = millis();

    int seconds = milliseconds / 1000;
    milliseconds %= 1000;

    int minutes = seconds / 60;
    seconds %= 60;

    int hours = minutes / 60;
    minutes %= 60;

    return String(hours) + ":" + String(minutes) + ":" + String(seconds) + ":" + String(milliseconds);
}

String Logger::formatLogType(LogType logType)
{
    switch (logType)
    {
    case LogType::FATAL:
        return "FATAL";
    case LogType::ERROR:
        return "ERROR";
    case LogType::WARN:
        return "WARN";
    case LogType::INFO:
        return "INFO";
    default:
        return "UNKNOWN";
    }
}

void Logger::log(LogType logType, const char *message)
{
    String logMessage = formatSysTime() + " - " + formatLogType(logType) + " - " + message;
    outputLogMessage(logMessage);
    m_sdCardHandler->appendLogs(logMessage.c_str());
}

void Logger::outputLogMessage(const String &logMessage)
{
    Serial.println(logMessage);
}