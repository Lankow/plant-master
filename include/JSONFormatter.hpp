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

  JSONFormatter(DataProvider *p_dataProvider);
  String serialize(JSONType p_jsonType);

private:
  DataProvider *m_dataProvider;
  String buildHumidityJson();
  String createSensorJson(int sensorIndex);
  String createJsonProperty(const String &name, const String &value);
};
#endif // JSON_FORMATTER_HPP