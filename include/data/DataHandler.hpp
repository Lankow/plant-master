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

/**
 * @class DataHandler
 * @brief A class to handle data processing and storage.
 *
 * This class processes incoming data from various topics and stores it in the DataStorage object.
 */
class DataHandler
{
public:
    /**
     * @brief Constructs a new DataHandler object.
     *
     * @param dataStorage A shared pointer to a DataStorage object for storing data.
     */
    DataHandler(std::shared_ptr<DataStorage> dataStorage);

    /**
     * @brief Handles incoming data based on the topic and payload.
     *
     * @param topic The topic of the incoming data.
     * @param payload The payload of the incoming data.
     */
    void handleData(const std::string &topic, const std::string &payload);

private:
    std::shared_ptr<DataStorage> m_dataStorage; /**< A shared pointer to a DataStorage object. */
};

#endif // DATA_HANDLER_HPP