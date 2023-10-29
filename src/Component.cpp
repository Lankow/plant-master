/*
 *   Component.cpp
 *   ----------------------
 *   Created on: 2023/09/29
 *   Author: Lankow
 */
#include "Component.hpp"
#include "Logger.hpp"

void Component::setDataProvider(DataProvider *dataProvider)
{
  m_dataProvider = dataProvider;
};

void Component::setLogger(Logger *logger)
{
  m_logger = logger;
};
