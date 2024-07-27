/**
 * @file Constants.hpp
 * @date 2024-05-26
 * @version 1.0
 *
 * @brief This file contains various constants used throughout the Plant Master system.
 */

#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <string>
#include <cstdint>
#include <IPAddress.h>

namespace AnalogPin
{
  constexpr uint16_t MAX = 4095; /**< Maximum value for analog pin. */
  constexpr uint16_t MIN = 0;    /**< Minimum value for analog pin. */
}

namespace ResetButton
{
  constexpr uint16_t PIN = 0;                  /**< Pin number for the reset button. */
  constexpr uint16_t THRESHOLD_TIME_MS = 3000; /**< Threshold time in milliseconds for the reset button. */
  constexpr uint16_t DEFAULT_TIME = 0;         /**< Default time for the reset button. */
  const int DOUBLE_CLICK_THRESHOLD_MS = 1000;  /**< Time window for double click detection */
}

namespace HumiditySensor
{
  constexpr uint8_t MAX_AMOUNT = 4;                      /**< Maximum number of humidity sensors. */
  constexpr uint16_t DEFAULT_ACTIVE_PIN = 0;             /**< Default active pin for the humidity sensor. */
  constexpr uint16_t DEFAULT_HUMIDITY = AnalogPin::MAX;  /**< Default humidity value for the humidity sensor. */
  constexpr uint16_t DEFAULT_THRESHOLD = AnalogPin::MAX; /**< Default threshold value for the humidity sensor. */
}

namespace Room
{
  constexpr float DEFAULT_TEMPERATURE = 0.0f; /**< Default temperature for the room. */
  constexpr float DEFAULT_HUMIDITY = 0.0f;    /**< Default humidity for the room. */
}

namespace Screen
{
  constexpr uint16_t INITIAL_DURATION = 3000; /**< Initial screen duration in milliseconds. */
  constexpr uint8_t WIDTH = 128;              /**< OLED Screen Width. */
  constexpr uint8_t HEIGHT = 64;              /**< OLED Screen Height. */
  constexpr int16_t TEXT_X = 0;               /**< Text offset on X-axis. */
  constexpr int16_t TEXT_Y = 16;              /**< Text offset on Y-axis. */
  constexpr int16_t HEADING_X = 0;            /**< Heading offset on X-axis. */
  constexpr int16_t HEADING_Y = 4;            /**< Heading offset on Y-axis. */
  constexpr int16_t HEADING_LINE_Y = 14;      /**< Heading line offset on Y-axis. */
  constexpr int16_t TEXT_SIZE = 1;            /**< Default Text size for screen. */

  enum Type
  {
    None,
    InitialScreen,
    ResetScreen,
    AppScreen,
    ConfigScreen,
    HelpScreen,
    ErrorScreen
  };
}

namespace Network
{
  const std::string WEBSOCKET_URL = "/ws"; /**< URL for the WebSocket connection. */

  namespace Ports
  {
    constexpr uint16_t ASYNC_SERVER = 80;  /**< Port for the asynchronous server. */
    constexpr uint16_t MQTT_SERVER = 1883; /**< Port for the MQTT server. */
  }

  namespace IP
  {
    const IPAddress LOCAL(192, 168, 1, 184);       /**< Local IP address. */
    const IPAddress MQTT_SERVER(192, 168, 1, 184); /**< MQTT server IP address. */
    const IPAddress GATEWAY(192, 168, 1, 1);       /**< Gateway IP address. */
    const IPAddress SUBNET(255, 255, 0, 0);        /**< Subnet mask. */
    const IPAddress PRIMARY_DNS(8, 8, 8, 8);       /**< Primary DNS server IP address. */
    const IPAddress SECONDARY_DNS(8, 8, 4, 4);     /**< Secondary DNS server IP address. */
  }
}

namespace MQTT
{
  const std::string PLANT_HUMIDITY = "plant/humidity";     /**< MQTT topic for plant humidity. */
  const std::string ROOM_TEMPERATURE = "room/temperature"; /**< MQTT topic for room temperature. */
  const std::string ROOM_HUMIDITY = "room/humidity";       /**< MQTT topic for room humidity. */
  const std::string WATER_ACTIVE = "water/active";         /**< MQTT topic for water activation status. */
  const std::string WATER_PIN = "water/pin";               /**< MQTT topic for water pin. */
}

namespace JSON
{
  const std::string DHT_PIN = "dhtPin";              /**< JSON key for DHT sensor pin. */
  const std::string OLED_MOSI_PIN = "oledMosiPin";   /**< JSON key for OLED MOSI pin. */
  const std::string OLED_CLK_PIN = "oledClkPin";     /**< JSON key for OLED CLK pin. */
  const std::string OLED_DC_PIN = "oledDcPin";       /**< JSON key for OLED DC pin. */
  const std::string OLED_CS_PIN = "oledCsPin";       /**< JSON key for OLED CS pin. */
  const std::string OLED_RESET_PIN = "oledResetPin"; /**< JSON key for OLED RESET pin. */
  const std::string WATER_PUMP_PIN = "waterPumpPin"; /**< JSON key for water pump pin. */
  const std::string READER_PINS = "readerPins";      /**< JSON key for reader pins. */
  const std::string VALVE_PINS = "valvePins";        /**< JSON key for valve pins. */
  const std::string THRESHOLDS = "thresholds";       /**< JSON key for thresholds. */
}

namespace PumpState
{
  const std::string ACTIVE = "active";     /**< Pump state when active. */
  const std::string INACTIVE = "inactive"; /**< Pump state when inactive. */
}

#ifdef PLANT_MASTER
namespace Config
{
  constexpr uint32_t CYCLE_TIME_MS = 200;              /**< Cycle time in milliseconds for Plant Master. */
  const std::string PAGE_SSID = "config_plant_master"; /**< SSID for Plant Master configuration page. */
  const std::string PAGE_PASSWORD = "plantmaster";     /**< Password for Plant Master configuration page. */
  const std::string MQTT_IDENTIFIER = "PlantMaster";   /**< MQTT identifier for Plant Master. */
  const std::string PATH = "/config-master.json";      /**< Path to Plant Master configuration file. */
}
#else

namespace Config
{
  constexpr uint32_t CYCLE_TIME_MS = 1000;              /**< Cycle time in milliseconds for Plant Monitor. */
  const std::string PAGE_SSID = "config_plant_monitor"; /**< SSID for Plant Monitor configuration page. */
  const std::string PAGE_PASSWORD = "plantmonitor";     /**< Password for Plant Monitor configuration page. */
  const std::string MQTT_IDENTIFIER = "PlantMonitor";   /**< MQTT identifier for Plant Monitor. */
  const std::string PATH = "/config-monitor.json";      /**< Path to Plant Monitor configuration file. */
}
#endif

#endif // CONSTANTS_HPP
