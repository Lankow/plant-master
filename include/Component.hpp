/*
 *   Component.hpp
 *   ----------------------
 *   Created on: 2023/09/29
 *   Author: Lankow
 */
#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <Arduino.h>
#include <memory> // Include the memory header for std::shared_ptr
#include "DataProvider.hpp"

class Logger;

class Component
{
public:
  void setDataProvider(std::shared_ptr<DataProvider> dataProvider);

  virtual void init() = 0;
  virtual void cyclic() = 0;

protected:
  std::shared_ptr<DataProvider> m_dataProvider;
};

#endif // COMPONENT_HPP