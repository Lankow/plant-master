/*
 *   Constants.hpp
 *   ----------------------
 *   Created on: 2024/05/26
 *   Author: Lankow
 */
#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <string>

static const uint16_t ANALOG_PIN_MAX = 4095;
static const uint16_t ANALOG_PIN_MIN = 0;

static const uint16_t RESET_BUTTON_PIN = 0;
static const uint16_t RESET_THRESHOLD_TIME_MS = 3000;
static const uint16_t RESET_DEFAULT_TIME = 0;

static const uint8_t MAX_HUMIDITY_SENSORS_AMOUNT = 4;

static const uint16_t DEFAULT_HUMIDITY = ANALOG_PIN_MAX;
static const uint16_t DEFAULT_HUMIDITY_THRESHOLD = ANALOG_PIN_MAX;

static const uint16_t DEFAULT_ACTIVE_READER_PIN = 0;

static const float DEFAULT_ROOM_TEMPERATURE = 0;
static const float DEFAULT_ROOM_HUMIDITY = 0;

static const std::string WEBSOCKET_URL = "/ws";

static const uint16_t INITIAL_SCREEN_DURATION = 3000;

static const uint16_t ASYNC_SERVER_PORT = 80;
static const uint16_t MQTT_SERVER_PORT = 1883;

static const IPAddress LOCAL_IP(192, 168, 1, 184);
static const IPAddress MQTT_SERVER_IP(192, 168, 1, 184);
static const IPAddress GATEWAY(192, 168, 1, 1);

static const IPAddress SUBNET(255, 255, 0, 0);
static const IPAddress PRIMARY_DNS(8, 8, 8, 8);
static const IPAddress SECONDARY_DNS(8, 8, 4, 4);

static const std::string MQTT_PLANT_HUMIDITY = "plant/humidity";
static const std::string MQTT_ROOM_TEMPERATURE = "room/temperature";
static const std::string MQTT_ROOM_HUMIDITY = "room/humidity";
static const std::string MQTT_PUMP_ACTIVE = "pump/active";

static const std::string JSON_VERSION = "version";
static const std::string JSON_DHT_PIN = "dhtPin";
static const std::string JSON_WATER_PUMP_PIN = "waterPumpPin";
static const std::string JSON_READER_PINS = "readerPins";
static const std::string JSON_VALVE_PINS = "valvePins";
static const std::string JSON_THRESHOLDS = "thresholds";

static const std::string PUMP_ACTIVE = "active";
static const std::string PUMP_INACTIVE = "inactive";

#ifdef PLANT_MASTER
static const uint32_t CYCLE_TIME_MS = 200;

static const std::string CONFIG_PAGE_SSID = "config_plant_master";
static const std::string CONFIG_PAGE_PASSWORD = "plantmaster";
static const std::string MQTT_IDENTIFIER = "PlantMaster";

static const std::string CONFIG_PATH = "/config-master.json";

#else
static const uint32_t CYCLE_TIME_MS = 1000;

static const std::string CONFIG_PAGE_SSID = "config_plant_monitor";
static const std::string CONFIG_PAGE_PASSWORD = "plantmonitor";
static const std::string MQTT_IDENTIFIER = "PlantMonitor";

static const std::string CONFIG_PATH = "/config-monitor.json";
#endif

// ESP PINS
enum EspPins : uint8_t
{
  PIN_LED_BUILTIN = 2,
  PIN_4 = 4,
  PIN_5 = 5,
  PIN_12 = 12,
  PIN_14 = 14,
  PIN_17 = 17,
  PIN_18 = 18,
  PIN_19 = 19,
  PIN_20 = 20,
  PIN_21 = 21,
  PIN_22 = 22,
  PIN_23 = 23,
  PIN_32 = 32,
  PIN_34 = 34,
  PIN_35 = 35
};

#endif // CONSTANTS_HPP