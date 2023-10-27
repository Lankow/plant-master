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
private:
  DataProvider *m_dataProvider;
  Logger *m_logger;

protected:
  DataProvider *getDataProvider() const;
  Logger *getLogger() const;

public:
  void subscribeDataProvider(DataProvider *p_dataProvider);
  void subscribeLogger(Logger *p_logger);

  virtual void init();
  virtual void cyclic();
};

#endif // COMPONENT_HPP