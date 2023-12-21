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
  SDCardHandler(const uint8_t pinSck, const uint8_t pinMiso, const uint8_t pinMosi, const uint8_t pinCs);

  void init() override;
  void cyclic() override;

private:
  SPIClass m_spi;

  void initSDCard();
};

#endif // SD_CARD_HANDLER_HPP
