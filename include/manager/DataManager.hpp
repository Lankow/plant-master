/*
*   DataManager.hpp
*   ----------------------
*   Created on: 2023/10/09
*   Author: Lankow
*/
#ifndef DATA_MANAGER_HPP
#define DATA_MANAGER_HPP

#include "DataProvider.hpp"
#include "Component.hpp"

class DataManager : public Component{
    private:
        void checkHumidity();
    public:
        void cyclic();
};

#endif // DATA_MANAGER_HPP
