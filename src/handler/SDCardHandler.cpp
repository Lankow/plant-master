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
    Logger::log("Card Mount Failed");
    return;
  }
  uint8_t cardType = SD.cardType();

  if(cardType == CARD_NONE){
    Logger::log("No SD card attached");
    return;
  }

  Serial.print("SD Card Type: ");
  if(cardType == CARD_MMC){
    Logger::log("MMC");
  } else if(cardType == CARD_SD){
    Logger::log("SDSC");
  } else if(cardType == CARD_SDHC){
    Logger::log("SDHC");
  } else {
    Logger::log("UNKNOWN");
  }
  uint64_t cardSize = SD.cardSize() / (1024 * 1024);
  Serial.printf("SD Card Size: %lluMB\n", cardSize);
}

void SDCardHandler::listDir(fs::FS &fs, const char * dirname, uint8_t levels){
  Serial.printf("Listing directory: %s\n", dirname);

  File root = fs.open(dirname);
  if(!root){
    Logger::log("Failed to open directory");
    return;
  }
  if(!root.isDirectory()){
    Logger::log("Not a directory");
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

void SDCardHandler::createDir(fs::FS &fs, const char * path){
  Serial.printf("Creating Dir: %s\n", path);
  if(fs.mkdir(path)){
    Logger::log("Dir created");
  } else {
    Logger::log("mkdir failed");
  }
}

void SDCardHandler::removeDir(fs::FS &fs, const char * path){
  Serial.printf("Removing Dir: %s\n", path);
  if(fs.rmdir(path)){
    Logger::log("Dir removed");
  } else {
    Logger::log("rmdir failed");
  }
}

void SDCardHandler::readFile(fs::FS &fs, const char * path){
  Serial.printf("Reading file: %s\n", path);

  File file = fs.open(path);
  if(!file){
    Logger::log("Failed to open file for reading");
    return;
  }

  Serial.print("Read from file: ");
  while(file.available()){
    Serial.write(file.read());
  }
  file.close();
}

void SDCardHandler::writeFile(fs::FS &fs, const char * path, const char * message){
  Serial.printf("Writing file: %s\n", path);

  File file = fs.open(path, FILE_WRITE);
  if(!file){
    Logger::log("Failed to open file for writing");
    return;
  }
  if(file.print(message)){
    Logger::log("File written");
  } else {
    Logger::log("Write failed");
  }
  file.close();
}

void SDCardHandler::appendFile(fs::FS &fs, const char * path, const char * message){
  Serial.printf("Appending to file: %s\n", path);

  File file = fs.open(path, FILE_APPEND);
  if(!file){
    Logger::log("Failed to open file for appending");
    return;
  }
  if(file.print(message)){
    Logger::log("Message appended");
  } else {
    Logger::log("Append failed");
  }
  file.close();
}

void SDCardHandler::renameFile(fs::FS &fs, const char * path1, const char * path2){
  Serial.printf("Renaming file %s to %s\n", path1, path2);
  if (fs.rename(path1, path2)) {
    Logger::log("File renamed");
  } else {
    Logger::log("Rename failed");
  }
}

void SDCardHandler::deleteFile(fs::FS &fs, const char * path){
  Serial.printf("Deleting file: %s\n", path);
  if(fs.remove(path)){
    Logger::log("File deleted");
  } else {
    Logger::log("Delete failed");
  }
}

void SDCardHandler::init(){
  Logger::log("SDCardHandler - Init");
  initSDCard();
}