/*
*   TimeHandler.hpp
*   ----------------------
*   Created on: 2023/09/27
*   Author: Lankow
*/
#ifndef TIME_HANDLER_HPP
#define TIME_HANDLER_HPP

#include "Component.hpp"

class TimeHandler : public Component
{   
    void handleTime();
    
    public:
    void init();
    void cyclic();
};
#endif // TIME_HANDLER_HPP