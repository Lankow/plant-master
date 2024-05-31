/*
 *   JSONConverter.hpp
 *   ----------------------
 *   Created on: 2024/05/31
 *   Author: Lankow
 */
#ifndef JSON_CONVERTER_HPP
#define JSON_CONVERTER_HPP

#include <Arduino.h>
#include <ArduinoJson.h>
#include <memory>
#include "DataStorage.hpp"

class JSONConverter
{
    public:
    JSONConverter();

    std::string serializeDataStorage(const std::shared_ptr<DataStorage> &dataStorage);

    private:
};

#endif // JSON_CONVERTER_HPP