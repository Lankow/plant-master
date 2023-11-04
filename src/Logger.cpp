/*
 *   Logger.cpp
 *   ----------------------
 *   Created on: 2023/10/09
 *   Author: Lankow
 */
#include <Arduino.h>
#include "Logger.hpp"
#include "TimeConverter.hpp"

Logger::Logger(std::shared_ptr<SDCardHandler> sdCardHandler) : m_sdCardHandler(sdCardHandler) {}

std::string Logger::formatSysTime()
{
    long systemSeconds = millis() / 1000;
    return TimeConverter::convertTime(TimeConverter::ConverstionType::LOG, systemSeconds);
}

std::string Logger::formatLogType(LogType logType)
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
    std::string logMessage = formatSysTime() + " - " + formatLogType(logType) + " - " + message;
    outputLogMessage(logMessage);
    m_sdCardHandler->appendLogs(logMessage.c_str());
}

void Logger::outputLogMessage(const std::string &logMessage)
{
    Serial.println(logMessage.c_str());
}