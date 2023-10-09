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

    public:
    HumidityHandler(uint8_t pin);
    
    void readHumidity();
    void cyclic();
};

#endif // HUMIDITY_HANDLER_HPP
