/*
 *   constants.hpp
 *   ----------------------
 *   Created on: 2023/09/26
 *   Author: Lankow
 */
#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

// MIN MAX VALUES
static const uint8_t MAX_SENSORS_NO = 8;
static const uint8_t MAX_RETRIES = 10;

static const uint16_t ANALOG_PIN_MAX = 4095;
static const uint16_t ANALOG_PIN_MIN = 0;

static const uint16_t MIN_TIME_VAL = 1000;

// NETWORK CONSTANTS
static const std::string NTP_SERVER_PL_0 = "0.pl.pool.ntp.org";
static const std::string NTP_SERVER_PL_1 = "0.pl.pool.ntp.org";
static const std::string NTP_SERVER_PL_2 = "2.pl.pool.ntp.org";

static const long GMT_OFFSET = 0;
static const int DAY_OFFSET = 3600;

static const uint8_t NO_SENSOR = 0xFF;
static const uint8_t FIRST_SENSOR = 0;
static const uint8_t LAST_SENSOR = MAX_SENSORS_NO;

static const uint8_t PUMP_ON = 1;
static const uint8_t PUMP_OFF = 0;

static const IPAddress LOCAL_IP(192, 168, 1, 184);
static const IPAddress GATEWAY(192, 168, 1, 1);

static const IPAddress SUBNET(255, 255, 0, 0);
static const IPAddress PRIMARY_DNS(8, 8, 8, 8);
static const IPAddress SECONDARY_DNS(8, 8, 4, 4);

// DEFAULT VALUES
static const long DEFAULT_TIME = 0;
static const float DEFAULT_TEMPERATURE = 0;
static const float DEFAULT_ROOM_HUMIDITY = 0;
static const uint8_t DEFAULT_CYCLES = 0;

static const uint16_t DEFAULT_HUMIDITY_LVL = ANALOG_PIN_MAX;
static const uint16_t DEFAULT_THRESHOLD = ANALOG_PIN_MAX;
static const bool DEFAULT_ACTIVE = false;

// ERROR VALUES
static const std::string CONVERSION_ERROR = "YY-MM-DD HH-MM-SS";

// ESP PINS
enum EspPins : uint8_t
{
  PIN_LED_BUILTIN = 2,
  PIN_4 = 4,
  PIN_5 = 5,
  PIN_17 = 17,
  PIN_18 = 18,
  PIN_19 = 19,
  PIN_20 = 20,
  PIN_21 = 21,
  PIN_23 = 23,
  PIN_32 = 32,
  PIN_34 = 34,
  PIN_35 = 35
};

// OTHER CONSTANTS
#define DHT_TYPE DHT11
#define SYSTIME_LENGTH 16

#endif // CONSTANTS_HPP