/*
 *   Constants.hpp
 *   ----------------------
 *   Created on: 2024/05/26
 *   Author: Lankow
 */
#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <string>

static const std::string CONFIG_PAGE_SSID = "config_plant_master";
static const std::string CONFIG_PAGE_PASSWORD = "plantmaster";
static const std::string WEBSOCKET_URL = "/ws";

static const uint16_t INITIAL_SCREEN_DURATION = 3000;
static const uint16_t ASYNC_SERVER_PORT = 80;

static const IPAddress LOCAL_IP(192, 168, 1, 184);
static const IPAddress GATEWAY(192, 168, 1, 1);

static const IPAddress SUBNET(255, 255, 0, 0);
static const IPAddress PRIMARY_DNS(8, 8, 8, 8);
static const IPAddress SECONDARY_DNS(8, 8, 4, 4);

#endif // CONSTANTS_HPP