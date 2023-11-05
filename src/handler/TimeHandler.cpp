/*
 *   TimeHandler.cpp
 *   ----------------------
 *   Created on: 2023/09/27
 *   Author: Lankow
 */
#include <Arduino.h>
#include <chrono>
#include "handler/TimeHandler.hpp"
#include "constants.hpp"
#include "Logger.hpp"

void TimeHandler::handleTime()
{
    auto now = std::chrono::system_clock::now();
    std::time_t in_time_t = std::chrono::system_clock::to_time_t(now);
    m_dataProvider->setCurrentTime(in_time_t);
}

bool TimeHandler::retrieveTimeWithRetries(const int maxRetries, const int retryDelayMs)
{
    for (int i = 0; i < maxRetries; i++)
    {
        handleTime();
        if (m_dataProvider->getCurrentTime() > MIN_TIME_VAL)
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
