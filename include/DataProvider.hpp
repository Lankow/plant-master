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

// DataProvider to store all the information that could be forwarded
// Handlers have a handle on a dataProvider and on cyclics fill data
// DataManager on cyclic checks and manages the data e.g. humidity thresholds

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
