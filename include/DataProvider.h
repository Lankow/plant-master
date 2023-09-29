/*
*   DataProvider.h
*   ----------------------
*   Created on: 2023/09/29
*   Author: Lankow
*/
#ifndef DATA_PROVIDER_H
#define DATA_PROVIDER_H

#include "HumidityHandler.h"
#include "NetworkHandler.h"

class DataProvider
{
    private:
    HumidityHandler *m_humidityHandler;
    NetworkHandler *m_networkHandler;

    public:
    DataProvider(HumidityHandler *p_humidityHandler, NetworkHandler *p_networkHandler);
    
    int getHumidity();
    void setThreshold(int threshold);

};
#endif // DATA_PROVIDER_H
