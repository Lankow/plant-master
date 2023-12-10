/*
 *   SDCardUtil.cpp
 *   ----------------------
 *   Created on: 2023/12/10
 *   Author: Lankow
 */
#include "utils/SDCardUtil.hpp"
#include "utils/TimeUtil.hpp"
#include "constants.hpp"

void SDCardUtil::createLogs()
{
  std::string dateString = TimeUtil::getStringTime(TimeUtil::TimeType::FILE);
  m_logName = "/log-" + dateString + ".txt";

  File file = SD.open(m_logName.c_str(), FILE_WRITE);
  if (!file)
  {
    Serial.println("Failed to open file for writing");
    return;
  }
  if (file.print(m_logName.c_str()))
  {
    Serial.println("File written");
  }
  else
  {
    Serial.println("Write failed");
  }
  file.close();
}

void SDCardUtil::appendLogs(const std::string &message)
{
  File file = SD.open(m_logName.c_str(), FILE_APPEND);
  if (!file)
  {
    Serial.println("Failed to open file for appending");
    return;
  }
  if (file.print(message.c_str()))
  {
    Serial.println("Message appended");
  }
  else
  {
    Serial.println("Append failed");
  }
  file.close();
}
