/*
*   DataProvider.hpp
*   ----------------------
*   Created on: 2023/09/29
*   Author: Lankow
*/
#ifndef DATA_PROVIDER_HPP
#define DATA_PROVIDER_HPP

#include "handler/HumidityHandler.hpp"
#include "handler/NetworkHandler.hpp"
#include "handler/TimeHandler.hpp"

class DataProvider
{
    private:
    HumidityHandler *m_humidityHandler;
    NetworkHandler *m_networkHandler;
    TimeHandler *m_timeHandler;

    public:
    DataProvider(HumidityHandler *p_humidityHandler, NetworkHandler *p_networkHandler, TimeHandler *p_timeHandler);
    
    int getHumidity();
    String getTime();
    void setThreshold(int threshold);

};
#endif // DATA_PROVIDER_HPP
