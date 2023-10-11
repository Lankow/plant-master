/*
*   PumpHandler.hpp
*   ----------------------
*   Created on: 2023/10/01
*   Author: Lankow
*/
#ifndef PUMP_HANDLER_HPP
#define PUMP_HANDLER_HPP

#include "Component.hpp"

class PumpHandler : public Component{

    public:
      void checkAndPump();
      void cyclic();

};
#endif // PUMP_HANDLER_HPP