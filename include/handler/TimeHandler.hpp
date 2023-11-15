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
public:
    void init() override;
    void cyclic() override;

private:
    void handleTime();
    bool retrieveTimeWithRetries(const int maxRetries, const int retryDelayMs);
};
#endif // TIME_HANDLER_HPP