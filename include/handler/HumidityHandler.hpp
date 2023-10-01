/*
*   HumidityHandler.hpp
*   ----------------------
*   Created on: 2023/09/26
*   Author: Lankow
*/
#ifndef HUMIDITY_HANDLER_HPP
#define HUMIDITY_HANDLER_HPP

#include "Handler.hpp"

class HumidityHandler : public Handler
{
    private:
    int m_operatedPin;
    int m_currentHumidityLvl;
    int m_humidityThreshold;
    bool m_needsWatering;

    void compareHumidity();

    public:
    HumidityHandler(int pin, int threshold);
    
    void readHumidity();
    void setHumidityThreshold(int value);
    void setOperatedPin(int pin);

    bool getNeedsWatering();
    int getCurrentHumidity();
};

#endif // HUMIDITY_HANDLER_HPP
