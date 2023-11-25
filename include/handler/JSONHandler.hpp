/*
 *   JSONHandler.hpp
 *   ----------------------
 *   Created on: 2023/10/20
 *   Author: Lankow
 */
#ifndef JSON_FORMATTER_HPP
#define JSON_FORMATTER_HPP

#include <memory> // Include the memory header for std::shared_ptr
#include <ArduinoJson.h>
#include "DataProvider.hpp"

class JSONHandler
{
public:
  enum JSONType
  {
    ROOM_HUMIDITY,
    HUMIDITY,
    TEMPERATURE,
    TIME,
    SENSOR
  };

  JSONHandler(std::shared_ptr<DataProvider> dataProvider);
  void handleData(uint8_t *data, size_t len);
  const std::string serialize(const JSONType jsonType);

private:
  std::shared_ptr<DataProvider> m_dataProvider;
  StaticJsonDocument<BUFFER_SIZE> m_receivedJson;

  const std::string buildHumidityJson();
  const std::string createSensorJson(const int sensorIndex);
  const std::string createJsonProperty(const std::string &name, const std::string &value);
};
#endif // JSON_FORMATTER_HPP