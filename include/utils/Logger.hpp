/*
 *   Logger.hpp
 *   ----------------------
 *   Created on: 2023/10/09
 *   Author: Lankow
 */
#ifndef LOGGER_HPP
#define LOGGER_HPP

#include "constants.hpp"

class Logger
{
public:
  enum LogType
  {
    FATAL,
    ERROR,
    WARN,
    INFO
  };

  static void log(LogType logType, const std::string message);

private:
  static std::string formatLogType(const LogType logType);
  static void outputLogMessage(const std::string &logMessage);
};

#endif // LOGGER_HPP