/*
 *   Logger.hpp
 *   ----------------------
 *   Created on: 2023/10/09
 *   Author: Lankow
 */
#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <memory.h>
#include "constants.hpp"

class Logger
{
public:
  Logger(std::shared_ptr<const SDCardHandler> sdCardHandler);

  enum LogType
  {
    FATAL,
    ERROR,
    WARN,
    INFO
  };

  void log(LogType logType, const std::string message);

private:
  std::shared_ptr<const SDCardHandler> m_sdCardHandler;
  std::string m_formattedSysTime[SYSTIME_LENGTH];

  std::string formatSysTime();
  std::string formatLogType(const LogType logType);
  void outputLogMessage(const std::string &logMessage);
};

#endif // LOGGER_HPP