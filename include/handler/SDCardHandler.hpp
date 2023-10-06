/*
*   SDCardHandler.hpp
*   ----------------------
*   Created on: 2023/10/06
*   Author: Lankow
*/
#include "FS.h"
#include "SD.h"
#include "SPI.h"

#ifndef SD_CARD_HANDLER_HPP
#define SD_CARD_HANDLER_HPP

class SDCardHandler
{
  private: 
  SPIClass m_spi;
  
  public:
    void createDir(fs::FS &fs, const char * path);
    void removeDir(fs::FS &fs, const char * path);
    void readFile(fs::FS &fs, const char * path);
    void writeFile(fs::FS &fs, const char * path, const char * message);
    void appendFile(fs::FS &fs, const char * path, const char * message);
    void renameFile(fs::FS &fs, const char * path1, const char * path2);
    void deleteFile(fs::FS &fs, const char * path);
};

#endif // SD_CARD_HANDLER_HPP
