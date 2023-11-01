/*
 *   JSONFormatter.hpp
 *   ----------------------
 *   Created on: 2023/10/20
 *   Author: Lankow
 */
#ifndef JSON_FORMATTER_HPP
#define JSON_FORMATTER_HPP
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

  JSONFormatter(DataProvider *dataProvider);
  std::string serialize(JSONType jsonType);

private:
  DataProvider *m_dataProvider;
  std::string buildHumidityJson();
  std::string createSensorJson(int sensorIndex);
  std::string createJsonProperty(const std::string &name, const std::string &value);
};
#endif // JSON_FORMATTER_HPP