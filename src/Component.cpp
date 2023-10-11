/*
*   Component.cpp
*   ----------------------
*   Created on: 2023/09/29
*   Author: Lankow
*/
#include "Component.hpp"

void Component::subscribeDataProvider(DataProvider *p_dataProvider){
  if(NULL != p_dataProvider){
    m_dataProvider = p_dataProvider;
  }
};

DataProvider* Component::getDataProvider() const{
        return m_dataProvider;
}

void Component::init(){};

void Component::cyclic(){};