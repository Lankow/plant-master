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
#include "Logger.hpp"
class Component
{
  private:
    DataProvider* m_dataProvider;

  protected:
    DataProvider* getDataProvider() const;

  public:
    void subscribeDataProvider(DataProvider *p_dataProvider);
    
    virtual void init();
    virtual void cyclic();
};

#endif // COMPONENT_HPP