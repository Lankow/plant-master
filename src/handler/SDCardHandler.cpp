/*
 *   SDCardHandler.cpp
 *   ----------------------
 *   Created on: 2023/10/06
 *   Author: Lankow
 */
#include "handler/SDCardHandler.hpp"

SDCardHandler::SDCardHandler(const uint8_t pinSck, const uint8_t pinMiso, const uint8_t pinMosi, const uint8_t pinCs) : m_spi(VSPI)
{
  m_spi.begin(pinSck, pinMiso, pinMosi, pinCs);
};

void SDCardHandler::initSDCard()
{
  if (!SD.begin())
  {
    // Log - "Card Mount Failed"
    return;
  }
  uint8_t cardType = SD.cardType();

  if (cardType == CARD_NONE)
  {
    // Log - "No SD card attached"
    return;
  }

  uint64_t cardSize = SD.cardSize() / (1024 * 1024);
  Serial.printf("SD Card Size: %lluMB\n", cardSize);
}

void SDCardHandler::init()
{
  // Log - "SDCardHandler - Init"
  initSDCard();
}

void SDCardHandler::cyclic()
{
  // Log - "SDCardHandler - Cyclic Task"
}