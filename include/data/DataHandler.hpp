/**
 * @file DataHandler.hpp
 * @date   2024-06-07
 * @author Lankow
 * @version 1.0
 *
 * @brief This file contains the definition of the DataHandler class.
 *
 * This class processes incoming data from various topics and stores it in the DataStorage object.
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