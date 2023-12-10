/*
 *   TimeUtil.hpp
 *   ----------------------
 *   Created on: 2023/09/27
 *   Author: Lankow
 */
#ifndef TIME_UTIL_HPP
#define TIME_UTIL_HPP
#include <Arduino.h>

class TimeUtil
{
public:
    enum TimeType
    {
        FILE,
        JSON,
        LOG
    };

    static time_t getSystemTime();
    static time_t getDateTime();
    static std::string getStringTime(const TimeType type);
};
#endif // TIME_UTIL_HPP