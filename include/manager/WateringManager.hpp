/*
 *   WateringManager.hpp
 *   ----------------------
 *   Created on: 2023/10/09
 *   Author: Lankow
 */
#ifndef DATA_MANAGER_HPP
#define DATA_MANAGER_HPP

#include "DataProvider.hpp"
#include "Component.hpp"

class WateringManager : public Component
{
private:
    Status checkHumidity();

public:
    void init() override;
    void cyclic() override;
};

#endif // DATA_MANAGER_HPP
