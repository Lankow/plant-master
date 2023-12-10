/*
 *   SDCardUtil.hpp
 *   ----------------------
 *   Created on: 2023/12/10
 *   Author: Lankow
 */

#ifndef SD_CARD_UTIL_HPP
#define SD_CARD_UTIL_HPP

#include "FS.h"
#include "SD.h"
#include "SPI.h"

class SDCardUtil
{
public:
  static void createLogs();
  static void appendLogs(const std::string &message);

private:
  static std::string m_logName;
};

#endif // SD_CARD_UTIL_HPP
