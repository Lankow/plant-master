/*
 *   Component.cpp
 *   ----------------------
 *   Created on: 2023/09/29
 *   Author: Lankow
 */
#include "Component.hpp"
#include "utils/Logger.hpp"

void Component::setDataProvider(std::shared_ptr<DataProvider> dataProvider)
{
  m_dataProvider = dataProvider;
};
