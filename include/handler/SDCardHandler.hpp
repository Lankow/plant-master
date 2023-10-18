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
  private: 
    SPIClass m_spi;

    void initSDCard();
  
    void listDir(fs::FS &fs, const char * dirname, uint8_t levels);
    void writeFile(fs::FS &fs, const char * path, const char * message);
    void appendFile(fs::FS &fs, const char * path, const char * message);
    void renameFile(fs::FS &fs, const char * path1, const char * path2);

  public:
    SDCardHandler(uint8_t pinSck, uint8_t pinMiso, uint8_t pinMosi, uint8_t pinCs);

    void init();
};

#endif // SD_CARD_HANDLER_HPP
