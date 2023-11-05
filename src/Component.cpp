/*
 *   Component.cpp
 *   ----------------------
 *   Created on: 2023/09/29
 *   Author: Lankow
 */
#include "Component.hpp"
#include "Logger.hpp"

void Component::setDataProvider(std::shared_ptr<DataProvider> dataProvider)
{
  m_dataProvider = dataProvider;
};

void Component::setLogger(std::shared_ptr<Logger> logger)
{
  m_logger = logger;
};
