/*
 *   constants.hpp
 *   ----------------------
 *   Created on: 2023/09/26
 *   Author: Lankow
 */
#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#define ANALOG_PIN_MAX 4095
#define ANALOG_PIN_MIN 0

#define MAX_SENSORS_NO 10

/* ESP PINS */
#define PIN_LED_BUILTIN 2

#define PIN_5 5

#define PIN_17 17
#define PIN_18 18
#define PIN_19 19
#define PIN_20 20
#define PIN_21 21

#define PIN_23 23

#define PIN_34 34
#define PIN_35 35

#define MAX_RETRIES 10

#define NTP_SERVER_PL_0 "0.pl.pool.ntp.org"
#define NTP_SERVER_PL_1 "0.pl.pool.ntp.org"
#define NTP_SERVER_PL_2 "2.pl.pool.ntp.org"

#define GMT_OFFSET 0
#define DAY_OFFSET 7200

#define DHT_TYPE DHT11

#define NO_SENSOR 0xFF
#define FIRST_SENSOR 0
#define LAST_SENSOR 10

#define TIMESTAMP_LENGTH 16
#define LOGNAME_LENGTH 24
#define SYSTIME_LENGTH 16

// DEFAULT VALUES
#define DEFAULT_TIME "yymodd-hh-mm-ss"
#define DEFAULT_HUMIDITY_LVL ANALOG_PIN_MAX
#define DEFAULT_THRESHOLD ANALOG_PIN_MAX
#define DEFAULT_ACTIVE false

#endif // CONSTANTS_HPP