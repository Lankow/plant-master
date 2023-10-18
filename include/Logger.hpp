/*
*   Logger.hpp
*   ----------------------
*   Created on: 2023/10/09
*   Author: Lankow
*/
#ifndef LOGGER_HPP
#define LOGGER_HPP

class SDCardHandler;

class Logger{
  private:
    SDCardHandler* m_sdCardHandler;
    
  public:  
    Logger(SDCardHandler* p_sdCardHandler);

    enum LogType { FATAL, ERROR, WARN, INFO };

    static void log(LogType p_logType, const char* p_message);

};

#endif // LOGGER_HPP