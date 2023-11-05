/*
 *   SDCardHandler.cpp
 *   ----------------------
 *   Created on: 2023/10/06
 *   Author: Lankow
 */
#include "handler/SDCardHandler.hpp"
#include "Logger.hpp"
#include "TimeConverter.hpp"

SDCardHandler::SDCardHandler(const uint8_t pinSck, const uint8_t pinMiso, const uint8_t pinMosi, const uint8_t pinCs) : m_spi(VSPI)
{
  m_spi.begin(pinSck, pinMiso, pinMosi, pinCs);
};

void SDCardHandler::initSDCard()
{
  if (!SD.begin())
  {
    m_logger->log(Logger::ERROR, "Card Mount Failed");
    return;
  }
  uint8_t cardType = SD.cardType();

  if (cardType == CARD_NONE)
  {
    m_logger->log(Logger::ERROR, "No SD card attached");
    return;
  }

  uint64_t cardSize = SD.cardSize() / (1024 * 1024);
  Serial.printf("SD Card Size: %lluMB\n", cardSize);
}

void SDCardHandler::startLogs(const std::string &path, const std::string &message)
{
  Serial.printf("Writing file: %s\n", path);

  File file = SD.open(path.c_str(), FILE_WRITE);
  if (!file)
  {
    Serial.println("Failed to open file for writing");
    return;
  }
  if (file.print(message.c_str()))
  {
    Serial.println("File written");
  }
  else
  {
    Serial.println("Write failed");
  }
  file.close();
}

void SDCardHandler::appendLogs(const std::string &message) const
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

void SDCardHandler::init()
{
  m_logger->log(Logger::INFO, "SDCardHandler - Init");
  initSDCard();
  std::string dateString = TimeConverter::convertTime(TimeConverter::ConverstionType::FILE, m_dataProvider->getCurrentTime());
  m_logName = "/log-" + dateString + ".txt";
  startLogs(m_logName, "Plant-Master-Logs-Init");
}

void SDCardHandler::cyclic()
{
  m_logger->log(Logger::INFO, "SDCardHandler - Cyclic Task");
}