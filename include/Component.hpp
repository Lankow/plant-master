/*
 *   Component.hpp
 *   ----------------------
 *   Created on: 2023/09/29
 *   Author: Lankow
 */
#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <Arduino.h>
#include "DataProvider.hpp"

class Logger;

class Component
{
public:
  void setDataProvider(DataProvider *dataProvider);
  void setLogger(Logger *logger);

  virtual void init() = 0;
  virtual void cyclic() = 0;

protected:
  DataProvider *m_dataProvider;
  Logger *m_logger;
};

#endif // COMPONENT_HPP