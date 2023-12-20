/*
 *   SDCardUtil.cpp
 *   ----------------------
 *   Created on: 2023/12/10
 *   Author: Lankow
 */
#include "utils/SDCardUtil.hpp"
#include "utils/TimeUtil.hpp"
#include "constants.hpp"

std::string SDCardUtil::m_logName;

void SDCardUtil::createLogFile()
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

void SDCardUtil::appendLogFile(const std::string &message)
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

std::vector<std::string> SDCardUtil::getListOfLogFiles()
{
  std::vector<std::string> fileList;

  File root = SD.open("/");
  if (!root)
  {
    Serial.println("Failed to open directory");
    return fileList;
  }

  while (fileList.size() < MAX_LOG_FILES)
  {
    File entry = root.openNextFile();
    if (!entry)
    {
      break;
    }
    if (entry.isDirectory())
    {

      continue;
    }

    fileList.push_back(entry.name());

    entry.close();
  }

  root.close();
  return fileList;
}
