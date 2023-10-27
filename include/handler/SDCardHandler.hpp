/*
 *   SDCardHandler.hpp
 *   ----------------------
 *   Created on: 2023/10/06
 *   Author: Lankow
 */
#include "FS.h"
#include "SD.h"
#include "SPI.h"
#include "Component.hpp"

#ifndef SD_CARD_HANDLER_HPP
#define SD_CARD_HANDLER_HPP

class SDCardHandler : public Component
{
public:
  SDCardHandler(uint8_t pinSck, uint8_t pinMiso, uint8_t pinMosi, uint8_t pinCs);

  void init();

  friend class Logger;

private:
  SPIClass m_spi;
  String m_logName;

  void initSDCard();

  void startLogs(const char *path, const char *message);
  void appendLogs(const char *message);
};

#endif // SD_CARD_HANDLER_HPP
