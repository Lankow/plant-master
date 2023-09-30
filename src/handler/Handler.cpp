/*
*   Handler.cpp
*   ----------------------
*   Created on: 2023/09/29
*   Author: Lankow
*/
#include "handler/Handler.hpp"

void Handler::initDataProvider(DataProvider *p_dataProvider){
  if(NULL != p_dataProvider){
    m_dataProvider = p_dataProvider;
  }
};

DataProvider* Handler::getDataProvider() const{
        return m_dataProvider;
}