/*
*   Handler.cpp
*   ----------------------
*   Created on: 2023/09/29
*   Author: Lankow
*/
#include "handler/Handler.hpp"

void Handler::subscribeDataProvider(DataProvider *p_dataProvider){
  if(NULL != p_dataProvider){
    m_dataProvider = p_dataProvider;
  }
};

DataProvider* Handler::getDataProvider() const{
        return m_dataProvider;
}

void Handler::init(){
  Serial.println("Handler - Initialization");
};

void Handler::cyclic(){
  Serial.println("Handler - Cyclic Task");
};