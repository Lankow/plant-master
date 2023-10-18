/*
*   SDCardHandler.cpp
*   ----------------------
*   Created on: 2023/10/06
*   Author: Lankow
*/
#include "handler/SDCardHandler.hpp"

SDCardHandler::SDCardHandler(uint8_t pinSck, uint8_t pinMiso, uint8_t pinMosi, uint8_t pinCs): m_spi(VSPI){
  m_spi.begin(pinSck, pinMiso, pinMosi, pinCs);
};

void SDCardHandler::initSDCard(){
  if(!SD.begin()){
      Logger::log(getDataProvider()->getCurrentTime(), Logger::ERROR, "Card Mount Failed");
    return;
  }
  uint8_t cardType = SD.cardType();

  if(cardType == CARD_NONE){
      Logger::log(getDataProvider()->getCurrentTime(), Logger::ERROR, "No SD card attached");
    return;
  }

  Serial.print("SD Card Type: ");
  if(cardType == CARD_MMC){
      Logger::log(getDataProvider()->getCurrentTime(), Logger::INFO, "MMC");
  } else if(cardType == CARD_SD){
      Logger::log(getDataProvider()->getCurrentTime(), Logger::INFO, "SDSC");
  } else if(cardType == CARD_SDHC){
      Logger::log(getDataProvider()->getCurrentTime(), Logger::INFO, "SDHC");
  } else {
      Logger::log(getDataProvider()->getCurrentTime(), Logger::INFO, "UNKNOWN");
  }
  uint64_t cardSize = SD.cardSize() / (1024 * 1024);
  Serial.printf("SD Card Size: %lluMB\n", cardSize);
}

void SDCardHandler::writeFile(fs::FS &fs, const char * path, const char * message){
  Serial.printf("Writing file: %s\n", path);

  File file = fs.open(path, FILE_WRITE);
  if(!file){
    Serial.println("Failed to open file for writing");
    return;
  }
  if(file.print(message)){
    Serial.println("File written");
  } else {
    Serial.println("Write failed");
  }
  file.close();
}

void SDCardHandler::listDir(fs::FS &fs, const char * dirname, uint8_t levels){
  Serial.printf("Listing directory: %s\n", dirname);

  File root = fs.open(dirname);
  if(!root){
    Serial.println("Failed to open directory");
    return;
  }
  if(!root.isDirectory()){
    Serial.println("Not a directory");
    return;
  }

  File file = root.openNextFile();
  while(file){
    if(file.isDirectory()){
      Serial.print("  DIR : ");
      Serial.println(file.name());
      if(levels){
        listDir(fs, file.name(), levels -1);
      }
    } else {
      Serial.print("  FILE: ");
      Serial.print(file.name());
      Serial.print("  SIZE: ");
      Serial.println(file.size());
    }
     file = root.openNextFile();
  }
}

void SDCardHandler::init(){
  Logger::log(getDataProvider()->getCurrentTime(), Logger::INFO, "SDCardHandler - Init");

  initSDCard();
  String logTime = "/log-" + String(getDataProvider()->getCurrentTime()) + ".txt";
  writeFile(SD, logTime.c_str(), "log");
  listDir(SD, "/", 0);
}