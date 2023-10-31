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
#include "handler/SDCardHandler.hpp"

class Logger
{
public:
  Logger(std::shared_ptr<SDCardHandler> sdCardHandler);

  enum LogType
  {
    FATAL,
    ERROR,
    WARN,
    INFO
  };

  void log(LogType logType, const char *message);

private:
  std::shared_ptr<SDCardHandler> m_sdCardHandler;
  String m_formattedSysTime[SYSTIME_LENGTH];

  String formatSysTime();
  String formatLogType(LogType logType);
  void outputLogMessage(const String &logMessage);
};

#endif // LOGGER_HPP