/*
 *   JSONFormatter.hpp
 *   ----------------------
 *   Created on: 2023/10/20
 *   Author: Lankow
 */
#ifndef JSON_FORMATTER_HPP
#define JSON_FORMATTER_HPP

#include <memory> // Include the memory header for std::shared_ptr
#include "DataProvider.hpp"

class JSONFormatter
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

  JSONFormatter(std::shared_ptr<const DataProvider> dataProvider);
  std::string serialize(JSONType jsonType);

private:
  std::shared_ptr<const DataProvider> m_dataProvider;
  std::string buildHumidityJson();
  std::string createSensorJson(int sensorIndex);
  std::string createJsonProperty(const std::string &name, const std::string &value);
};
#endif // JSON_FORMATTER_HPP