/*
 *   TimeHandler.cpp
 *   ----------------------
 *   Created on: 2023/09/27
 *   Author: Lankow
 */
#include <Arduino.h>
#include "handler/TimeHandler.hpp"
#include "constants.hpp"
#include "Logger.hpp"

void TimeHandler::handleTime()
{
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo))
    {
        m_logger->log(Logger::ERROR, "Encountered Error when retrieving system time...");
        return;
    }
    m_dataProvider->setCurrentTime(timeinfo);
}

bool TimeHandler::retrieveTimeWithRetries(int maxRetries, int retryDelayMs)
{
    for (int i = 0; i < maxRetries; i++)
    {
        handleTime();
        if (m_dataProvider->getCurrentTime() != DEFAULT_TIME)
        {
            return true;
        }
        delay(retryDelayMs);
    }
    return false;
}

void TimeHandler::init()
{
    m_logger->log(Logger::INFO, "TimeHandler - Init");
    if (!retrieveTimeWithRetries(MAX_RETRIES, 1000))
    {
        m_logger->log(Logger::ERROR, "Failed to retrieve system time.");
    }
}

void TimeHandler::cyclic()
{
    m_logger->log(Logger::INFO, "TimeHandler - Cyclic Task");
    handleTime();
}
