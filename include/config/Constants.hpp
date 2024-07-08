/**
 * @file Constants.hpp
 * @date   2024-05-26
 * @author Lankow
 * @version 1.0
 *
 * @brief This file contains various constants used throughout the Plant Master system.
 */
#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <string>
#include <cstdint>
#include <IPAddress.h>

/**
 * @namespace AnalogPin
 * @brief Constants for analog pins.
 */
namespace AnalogPin
{
  static const uint16_t MAX = 4095; /**< Maximum value for analog pin. */
  static const uint16_t MIN = 0;    /**< Minimum value for analog pin. */
}

/**
 * @namespace ResetButton
 * @brief Constants for the reset button.
 */
namespace ResetButton
{
  static const uint16_t PIN = 0;                  /**< Pin number for the reset button. */
  static const uint16_t THRESHOLD_TIME_MS = 3000; /**< Threshold time in milliseconds for the reset button. */
  static const uint16_t DEFAULT_TIME = 0;         /**< Default time for the reset button. */
}

/**
 * @namespace HumiditySensor
 * @brief Constants for humidity sensors.
 */
namespace HumiditySensor
{
  static const uint8_t MAX_AMOUNT = 4;                      /**< Maximum number of humidity sensors. */
  static const uint16_t DEFAULT_ACTIVE_PIN = 0;             /**< Default active pin for the humidity sensor. */
  static const uint16_t DEFAULT_HUMIDITY = AnalogPin::MAX;  /**< Default humidity value for the humidity sensor. */
  static const uint16_t DEFAULT_THRESHOLD = AnalogPin::MAX; /**< Default threshold value for the humidity sensor. */
}

/**
 * @namespace Room
 * @brief Constants for room environment.
 */
namespace Room
{
  static const float DEFAULT_TEMPERATURE = 0.0f; /**< Default temperature for the room. */
  static const float DEFAULT_HUMIDITY = 0.0f;    /**< Default humidity for the room. */
}

/**
 * @namespace Screen
 * @brief Constants for screen display.
 */
namespace Screen
{
  static const uint16_t INITIAL_SCREEN_DURATION = 3000; /**< Initial screen duration in milliseconds. */
}

/**
 * @namespace Network
 * @brief Constants for network configuration.
 */
namespace Network
{
  static const std::string WEBSOCKET_URL = "/ws"; /**< URL for the WebSocket connection. */

  /**
   * @namespace Ports
   * @brief Constants for network ports.
   */
  namespace Ports
  {
    static const uint16_t ASYNC_SERVER = 80;  /**< Port for the asynchronous server. */
    static const uint16_t MQTT_SERVER = 1883; /**< Port for the MQTT server. */
  }

  /**
   * @namespace IP
   * @brief Constants for IP addresses.
   */
  namespace IP
  {
    static const IPAddress LOCAL(192, 168, 1, 184);       /**< Local IP address. */
    static const IPAddress MQTT_SERVER(192, 168, 1, 184); /**< MQTT server IP address. */
    static const IPAddress GATEWAY(192, 168, 1, 1);       /**< Gateway IP address. */
    static const IPAddress SUBNET(255, 255, 0, 0);        /**< Subnet mask. */
    static const IPAddress PRIMARY_DNS(8, 8, 8, 8);       /**< Primary DNS server IP address. */
    static const IPAddress SECONDARY_DNS(8, 8, 4, 4);     /**< Secondary DNS server IP address. */
  }
}

/**
 * @namespace MQTT
 * @brief Constants for MQTT topics.
 */
namespace MQTT
{
  static const std::string PLANT_HUMIDITY = "plant/humidity";     /**< MQTT topic for plant humidity. */
  static const std::string ROOM_TEMPERATURE = "room/temperature"; /**< MQTT topic for room temperature. */
  static const std::string ROOM_HUMIDITY = "room/humidity";       /**< MQTT topic for room humidity. */
  static const std::string WATER_ACTIVE = "water/active";         /**< MQTT topic for water activation status. */
  static const std::string WATER_PIN = "water/pin";               /**< MQTT topic for water pin. */
}

/**
 * @namespace JSON
 * @brief Constants for JSON keys.
 */
namespace JSON
{
  static const std::string DHT_PIN = "dhtPin";              /**< JSON key for DHT sensor pin. */
  static const std::string WATER_PUMP_PIN = "waterPumpPin"; /**< JSON key for water pump pin. */
  static const std::string READER_PINS = "readerPins";      /**< JSON key for reader pins. */
  static const std::string VALVE_PINS = "valvePins";        /**< JSON key for valve pins. */
  static const std::string THRESHOLDS = "thresholds";       /**< JSON key for thresholds. */
}

/**
 * @namespace PumpState
 * @brief Constants for pump states.
 */
namespace PumpState
{
  static const std::string ACTIVE = "active";     /**< Pump state when active. */
  static const std::string INACTIVE = "inactive"; /**< Pump state when inactive. */
}

#ifdef PLANT_MASTER
/**
 * @namespace Config
 * @brief Configuration constants for Plant Master.
 */
namespace Config
{
  static const uint32_t CYCLE_TIME_MS = 200;                  /**< Cycle time in milliseconds for Plant Master. */
  static const std::string PAGE_SSID = "config_plant_master"; /**< SSID for Plant Master configuration page. */
  static const std::string PAGE_PASSWORD = "plantmaster";     /**< Password for Plant Master configuration page. */
  static const std::string MQTT_IDENTIFIER = "PlantMaster";   /**< MQTT identifier for Plant Master. */
  static const std::string PATH = "/config-master.json";      /**< Path to Plant Master configuration file. */
}
#else
/**
 * @namespace Config
 * @brief Configuration constants for Plant Monitor.
 */
namespace Config
{
  static const uint32_t CYCLE_TIME_MS = 1000;                  /**< Cycle time in milliseconds for Plant Monitor. */
  static const std::string PAGE_SSID = "config_plant_monitor"; /**< SSID for Plant Monitor configuration page. */
  static const std::string PAGE_PASSWORD = "plantmonitor";     /**< Password for Plant Monitor configuration page. */
  static const std::string MQTT_IDENTIFIER = "PlantMonitor";   /**< MQTT identifier for Plant Monitor. */
  static const std::string PATH = "/config-monitor.json";      /**< Path to Plant Monitor configuration file. */
}
#endif

#endif // CONSTANTS_HPP