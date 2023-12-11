/*
 *   JSONUtil.hpp
 *   ----------------------
 *   Created on: 2023/10/20
 *   Author: Lankow
 */
#ifndef JSON_UTIL_HPP
#define JSON_UTIL_HPP

#include <memory> // Include the memory header for std::shared_ptr
#include <ArduinoJson.h>
#include "DataProvider.hpp"

class JSONUtil
{
public:
  static void handleData(std::shared_ptr<DataProvider> dataProvider, uint8_t *data, size_t len);
  static std::string serialize(const std::shared_ptr<DataProvider> &dataProvider);

private:
  static JsonArray buildHumidityJson(const std::vector<HumidityData> &humidityData);
  static void createSensorJson(const HumidityData &humidityData, JsonArray &humidityArray, const int sensorIndex);
};
#endif // JSON_UTIL_HPP