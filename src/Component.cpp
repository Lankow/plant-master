/*
 *   Component.cpp
 *   ----------------------
 *   Created on: 2023/09/29
 *   Author: Lankow
 */
#include "Component.hpp"

void Component::subscribeDataProvider(DataProvider *p_dataProvider)
{
  if (NULL != p_dataProvider)
  {
    m_dataProvider = p_dataProvider;
  }
};

void Component::subscribeLogger(Logger *p_logger)
{
  if (NULL != p_logger)
  {
    m_logger = p_logger;
  }
};

DataProvider *Component::getDataProvider() const
{
  return m_dataProvider;
}

Logger *Component::getLogger() const
{
  return m_logger;
}

void Component::init(){};

void Component::cyclic(){};