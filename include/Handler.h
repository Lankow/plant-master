/*
*   Handler.h
*   ----------------------
*   Created on: 2023/09/29
*   Author: Lankow
*/
#ifndef HANDLER_H
#define HANDLER_H

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
};

#endif // HUMIDITY_HANDLER_H