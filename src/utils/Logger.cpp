/*
 *   Logger.cpp
 *   ----------------------
 *   Created on: 2023/10/09
 *   Author: Lankow
 */
#include <Arduino.h>
#include "utils/Logger.hpp"
#include "utils/TimeUtil.hpp"
#include "utils/SDCardUtil.hpp"

std::string Logger::formatLogType(const LogType logType)
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

void Logger::log(const LogType logType, const std::string message)
{
    std::string logMessage = TimeUtil::getStringTime(TimeUtil::TimeType::LOG) + " - " + formatLogType(logType) + " - " + message;
    outputLogMessage(logMessage);
    SDCardUtil::appendLogFile(message);
}

void Logger::outputLogMessage(const std::string &logMessage)
{
    // Serial.println(logMessage.c_str());
}