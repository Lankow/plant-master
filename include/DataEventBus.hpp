/*
 *   DataEventBus.hpp
 *   ----------------------
 *   Created on: 2023/12/06
 *   Author: Lankow
 */
#ifndef DATA_EVENT_BUS_HPP
#define DATA_EVENT_BUS_HPP

#include <functional>
#include <unordered_map>
#include <vector>
#include <ctime>
#include <boost/variant.hpp>

class DataEventBus
{
public:
  enum class EventType
  {
    CurrentTimeUpdated,
    TemperatureUpdated,
    RoomHumidityUpdated,
    HumidityDataUpdated,
    SensorToWaterUpdated,
    WateringCyclesUpdated
  };

  using EventData = boost::variant<std::time_t, float, float, uint8_t, uint8_t>;

  using EventCallback = std::function<void(const EventData &)>;

  void subscribe(EventType eventType, const EventCallback &callback);

  void publish(EventType eventType, const EventData &eventData) const;

private:
  std::unordered_map<int, std::vector<EventCallback>> subscribers;
};

#endif // DATA_EVENT_BUS_HPP
