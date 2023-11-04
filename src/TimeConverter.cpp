/*
 *   TimeConverter.cpp
 *   ----------------------
 *   Created on: 2023/11/04
 *   Author: Lankow
 */
#include <iomanip>
#include <sstream>
#include "TimeConverter.hpp"
#include "constants.hpp"

std::string TimeConverter::convertTime(ConverstionType type, time_t time)
{
  std::stringstream ss;

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