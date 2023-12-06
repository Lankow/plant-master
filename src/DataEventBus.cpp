/*
 *   DataEventBus.cpp
 *   ----------------------
 *   Created on: 2023/12/06
 *   Author: Lankow
 */
#include "DataEventBus.hpp"

void DataEventBus::subscribe(EventType eventType, const EventCallback &callback)
{
  subscribers[static_cast<int>(eventType)].push_back(callback);
}

void DataEventBus::publish(EventType eventType, const EventData &eventData) const
{
  auto it = subscribers.find(static_cast<int>(eventType));
  if (it != subscribers.end())
  {
    for (const auto &subscriber : it->second)
    {
      if (const auto *data = boost::get<std::time_t>(&eventData))
        subscriber(*data);
      else if (const auto *data = boost::get<float>(&eventData))
        subscriber(*data);
      else if (const auto *data = boost::get<uint8_t>(&eventData))
        subscriber(*data);
    }
  }
}