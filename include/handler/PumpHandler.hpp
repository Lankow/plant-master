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
      void handlePump();
      void cyclic();

};
#endif // PUMP_HANDLER_HPP