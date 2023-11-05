/*
 *   SDCardHandler.hpp
 *   ----------------------
 *   Created on: 2023/10/06
 *   Author: Lankow
 */

#ifndef SD_CARD_HANDLER_HPP
#define SD_CARD_HANDLER_HPP

#include "FS.h"
#include "SD.h"
#include "SPI.h"
#include "Component.hpp"

class SDCardHandler : public Component
{
public:
  SDCardHandler(uint8_t pinSck, uint8_t pinMiso, uint8_t pinMosi, uint8_t pinCs);

  void init() override;
  void cyclic() override;

  friend class Logger;

private:
  SPIClass m_spi;
  std::string m_logName;

  void initSDCard();

  void startLogs(const std::string &path, const std::string &message);
  void appendLogs(const std::string &message);
};

#endif // SD_CARD_HANDLER_HPP
