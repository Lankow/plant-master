/*
 *   DataHandler.hpp
 *   ----------------------
 *   Created on: 2024/06/07
 *   Author: Lankow
 */
#ifndef DATA_HANDLER_HPP
#define DATA_HANDLER_HPP

#include <Arduino.h>
#include <memory>
#include "data/DataStorage.hpp"

class DataHandler
{
public:
    DataHandler(std::shared_ptr<DataStorage> dataStorage);

    void handleData(const std::string &topic, const std::string &payload);

private:
    std::shared_ptr<DataStorage> m_dataStorage;
};

#endif // DATA_HANDLER_HPP