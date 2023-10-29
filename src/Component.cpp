/*
 *   Component.cpp
 *   ----------------------
 *   Created on: 2023/09/29
 *   Author: Lankow
 */
#include "Component.hpp"
#include "Logger.hpp"

void Component::setDataProvider(DataProvider *p_dataProvider)
{
  m_dataProvider = p_dataProvider;
};

void Component::setLogger(Logger *p_logger)
{
  m_logger = p_logger;
};
