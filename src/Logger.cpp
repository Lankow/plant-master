/*
*   Logger.cpp
*   ----------------------
*   Created on: 2023/10/09
*   Author: Lankow
*/
#include <Arduino.h>
#include "Logger.hpp"
#include "handler/SDCardHandler.hpp"

Logger::Logger(SDCardHandler* p_sdCardHandler) : m_sdCardHandler(p_sdCardHandler){};

void   Logger::log(const char* p_timestamp, LogType p_logType, const char* p_message) {
    String logType;
    String timestamp = p_timestamp;

    switch (p_logType) {
        case LogType::FATAL:
            logType = "FATAL";
        case LogType::ERROR:
            logType = "ERROR";
        case LogType::WARN:
            logType = "WARN";
        case LogType::INFO:
            logType = "INFO";
    }

    Serial.println(timestamp + " - " + logType + " - " + p_message);
}