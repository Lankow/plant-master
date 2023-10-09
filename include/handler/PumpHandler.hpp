/*
*   PumpHandler.hpp
*   ----------------------
*   Created on: 2023/10/01
*   Author: Lankow
*/
#ifndef PUMP_HANDLER_HPP
#define PUMP_HANDLER_HPP

#include "Handler.hpp"

class PumpHandler : public Handler{

    public:
      void checkAndPump();
      void cyclic();

};
#endif // PUMP_HANDLER_HPP