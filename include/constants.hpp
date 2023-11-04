/*
 *   constants.hpp
 *   ----------------------
 *   Created on: 2023/09/26
 *   Author: Lankow
 */
#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

// MIN MAX VALUES
#define MAX_SENSORS_NO 10
#define MAX_RETRIES 10

#define ANALOG_PIN_MAX 4095
#define ANALOG_PIN_MIN 0

#define MIN_TIME_VAL 1000

// NTP AND GMT CONSTANTS
#define NTP_SERVER_PL_0 "0.pl.pool.ntp.org"
#define NTP_SERVER_PL_1 "0.pl.pool.ntp.org"
#define NTP_SERVER_PL_2 "2.pl.pool.ntp.org"

#define GMT_OFFSET 0
#define DAY_OFFSET 3600

#define DHT_TYPE DHT11

#define NO_SENSOR 0xFF
#define FIRST_SENSOR 0
#define LAST_SENSOR 10

#define TIMESTAMP_LENGTH 16
#define LOGNAME_LENGTH 24
#define SYSTIME_LENGTH 16

// DEFAULT VALUES
#define DEFAULT_TIME 0
#define DEFAULT_TEMPERATURE 0
#define DEFAULT_ROOM_HUMIDITY 0

#define DEFAULT_HUMIDITY_LVL ANALOG_PIN_MAX
#define DEFAULT_THRESHOLD ANALOG_PIN_MAX
#define DEFAULT_ACTIVE false

// ERROR VALUES
#define CONVERSION_ERROR "YY-MM-DD HH-MM-SS"

/* ESP PINS */
enum EspPins : uint8_t
{
  PIN_LED_BUILTIN = 2,
  PIN_5 = 5,
  PIN_17 = 17,
  PIN_18 = 18,
  PIN_19 = 19,
  PIN_20 = 20,
  PIN_21 = 21,
  PIN_23 = 23,
  PIN_34 = 34,
  PIN_35 = 35
};

#endif // CONSTANTS_HPP