/*
*   Logger.hpp
*   ----------------------
*   Created on: 2023/10/09
*   Author: Lankow
*/
#ifndef LOGGER_HPP
#define LOGGER_HPP

class Component;

class Logger{
  private:
    Component* m_sdCardHandler;

  public:
    Logger(Component* p_sdCardHandler);

    static void log(const char* message);
};

#endif // LOGGER_HPP