/*
*   Logger.hpp
*   ----------------------
*   Created on: 2023/10/09
*   Author: Lankow
*/
#ifndef LOGGER_HPP
#define LOGGER_HPP
#include "constants.hpp"
#include "handler/SDCardHandler.hpp"

class Logger{
  public:  
    Logger(SDCardHandler* p_sdCardHandler);

    enum LogType { FATAL, ERROR, WARN, INFO };

    void log(LogType p_logType, const char* p_message);
  
  private:
    SDCardHandler* m_sdCardHandler;
    String m_formattedSysTime[SYSTIME_LENGTH];

    String formatSysTime();
    String formatLogType(LogType p_logType);
};

#endif // LOGGER_HPP