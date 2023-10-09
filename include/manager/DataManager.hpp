/*
*   DataManager.hpp
*   ----------------------
*   Created on: 2023/10/09
*   Author: Lankow
*/
#ifndef DATA_MANAGER_HPP
#define DATA_MANAGER_HPP

#include "DataProvider.hpp"

class DataManager {
    private:
    DataProvider* m_dataProvider;

    public:
    DataManager(DataProvider* p_dataProvider);

    void checkData();
};

#endif // DATA_MANAGER_HPP
