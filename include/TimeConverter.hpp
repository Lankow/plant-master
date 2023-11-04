/*
 *   TimeConverter.hpp
 *   ----------------------
 *   Created on: 2023/11/04
 *   Author: Lankow
 */
#ifndef TIME_CONVERTER_HPP
#define TIME_CONVERTER_HPP
#include <Arduino.h>

class TimeConverter
{
public:
  enum ConverstionType
  {
    FILE,
    JSON,
    LOG
  };

  static std::string convertTime(ConverstionType type, time_t time);
};
#endif // TIME_CONVERTER_HPP