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

class JSONHandler
{
public:
  JSONHandler(std::shared_ptr<DataProvider> dataProvider);
  void handleData(uint8_t *data, size_t len);
  const std::string serialize();

private:
  std::shared_ptr<DataProvider> m_dataProvider;
  StaticJsonDocument<BUFFER_SIZE> m_receivedJson;

  const JsonArray buildHumidityJson();
  void createSensorJson(JsonArray &humidityArray, const int sensorIndex);
};
#endif // JSON_UTIL_HPP