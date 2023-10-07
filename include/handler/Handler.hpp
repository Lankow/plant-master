/*
*   Handler.hpp
*   ----------------------
*   Created on: 2023/09/29
*   Author: Lankow
*/
#ifndef HANDLER_HPP
#define HANDLER_HPP

#include <Arduino.h>

class DataProvider;

class Handler
{
  private:
    DataProvider* m_dataProvider;

  protected:
    DataProvider* getDataProvider() const;

  public:
    void initDataProvider(DataProvider *p_dataProvider);
    
    void init();
    void cyclic();
};

#endif // HANDLER_HPP