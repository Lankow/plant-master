/*
*   Handler.hpp
*   ----------------------
*   Created on: 2023/09/29
*   Author: Lankow
*/
#ifndef HANDLER_HPP
#define HANDLER_HPP

#include <Arduino.h>
#include "DataProvider.hpp"
class Handler
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

#endif // HANDLER_HPP