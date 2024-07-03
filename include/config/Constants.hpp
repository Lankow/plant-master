/*
 *   Constants.hpp
 *   ----------------------
 *   Created on: 2024/05/26
 *   Author: Lankow
 */
#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <string>
#include <cstdint>
#include <IPAddress.h>

// Analog Pin Constants
namespace AnalogPin
{
  static const uint16_t MAX = 4095;
  static const uint16_t MIN = 0;
}

// Reset Button Constants
namespace ResetButton
{
  static const uint16_t PIN = 0;
  static const uint16_t THRESHOLD_TIME_MS = 3000;
  static const uint16_t DEFAULT_TIME = 0;
}

// Humidity Sensor Constants
namespace HumiditySensor
{
  static const uint8_t MAX_AMOUNT = 4;
  static const uint16_t DEFAULT_ACTIVE_PIN = 0;
  static const uint16_t DEFAULT_HUMIDITY = AnalogPin::MAX;
  static const uint16_t DEFAULT_THRESHOLD = AnalogPin::MAX;
}

// Room Environment Constants
namespace Room
{
  static const float DEFAULT_TEMPERATURE = 0.0f;
  static const float DEFAULT_HUMIDITY = 0.0f;
}

namespace Screen
{
  static const uint16_t INITIAL_SCREEN_DURATION = 3000;
}

// Network Constants
namespace Network
{
  static const std::string WEBSOCKET_URL = "/ws";

  namespace Ports
  {
    static const uint16_t ASYNC_SERVER = 80;
    static const uint16_t MQTT_SERVER = 1883;
  }

  namespace IP
  {
    static const IPAddress LOCAL(192, 168, 1, 184);
    static const IPAddress MQTT_SERVER(192, 168, 1, 184);
    static const IPAddress GATEWAY(192, 168, 1, 1);
    static const IPAddress SUBNET(255, 255, 0, 0);
    static const IPAddress PRIMARY_DNS(8, 8, 8, 8);
    static const IPAddress SECONDARY_DNS(8, 8, 4, 4);
  }
}

// MQTT Topics
namespace MQTT
{
  static const std::string PLANT_HUMIDITY = "plant/humidity";
  static const std::string ROOM_TEMPERATURE = "room/temperature";
  static const std::string ROOM_HUMIDITY = "room/humidity";
  static const std::string WATER_ACTIVE = "water/active";
  static const std::string WATER_PIN = "water/pin";
}

// JSON Keys
namespace JSON
{
  static const std::string DHT_PIN = "dhtPin";
  static const std::string WATER_PUMP_PIN = "waterPumpPin";
  static const std::string READER_PINS = "readerPins";
  static const std::string VALVE_PINS = "valvePins";
  static const std::string THRESHOLDS = "thresholds";
}

// Pump States
namespace PumpState
{
  static const std::string ACTIVE = "active";
  static const std::string INACTIVE = "inactive";
}

// Configuration for Plant Master and Monitor
#ifdef PLANT_MASTER
namespace Config
{
  static const uint32_t CYCLE_TIME_MS = 200;
  static const std::string PAGE_SSID = "config_plant_master";
  static const std::string PAGE_PASSWORD = "plantmaster";
  static const std::string MQTT_IDENTIFIER = "PlantMaster";
  static const std::string PATH = "/config-master.json";
}
#else
namespace Config
{
  static const uint32_t CYCLE_TIME_MS = 1000;
  static const std::string PAGE_SSID = "config_plant_monitor";
  static const std::string PAGE_PASSWORD = "plantmonitor";
  static const std::string MQTT_IDENTIFIER = "PlantMonitor";
  static const std::string PATH = "/config-monitor.json";
}
#endif

#endif // CONSTANTS_HPP