/*
 *   TimeHandler.cpp
 *   ----------------------
 *   Created on: 2023/09/27
 *   Author: Lankow
 */
#include <Arduino.h>
#include <chrono>
#include <iomanip>
#include <sstream>
#include "utils/TimeUtil.hpp"
#include "constants.hpp"

long TimeUtil::getSystemTime()
{
    long systemMs = millis();
    return systemMs;
};

time_t TimeUtil::getDateTime()
{
    auto now = std::chrono::system_clock::now();
    std::time_t in_time_t = std::chrono::system_clock::to_time_t(now);

    return in_time_t;
};

std::string TimeUtil::getStringTime(const TimeType type)
{
    std::stringstream ss;
    time_t time = getDateTime();

    switch (type)
    {
    case FILE:
        ss << std::put_time(std::localtime(&time), "%y%m%d %H-%M-%S");
        break;
    case JSON:
        ss << std::put_time(std::localtime(&time), "%Y-%m-%d %X");
        break;
    case LOG:
        ss << std::put_time(std::localtime(&time), "%H:%M:%S");
        break;
    default:
        ss << CONVERSION_ERROR;
    }

    return ss.str();
};