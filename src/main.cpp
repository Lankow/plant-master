#include <Arduino.h>
#include <Wire.h>  
#include "SSD1306Wire.h"
#include "OLEDDisplayUi.h"
#include <Preferences.h>
#include <WiFi.h>
#include <WebServer.h>

#define INITIAL_SCREEN_DURATION 3000
#define CONFIG_PAGE_SSID "config_plant_master"
#define CONFIG_PAGE_PASSWORD "plantmaster"

IPAddress ip(192, 168, 4, 1);
IPAddress netmask(255, 255, 255, 0);

SSD1306Wire display(0x3c, SDA, SCL); 
WebServer servidor(80);

void drawInitialScreen()
{
  display.clear();
  display.drawString(30, 10, "Plant-Master");
  display.drawHorizontalLine(10, 26, 100);
  display.drawString(35, 30, "by Lankow");
  display.display();
}

void drawConfigScreen(){
  display.clear();
  display.drawString(10,0, "Config SSID:");
  display.drawString(10,10, CONFIG_PAGE_SSID);
  display.drawHorizontalLine(10, 24, 100);
  display.drawString(10,25, "Config PASSWORD:");
  display.drawString(10,35, CONFIG_PAGE_PASSWORD);
  display.display();
}

void setupAccessPoint(){
    WiFi.mode(WIFI_AP);
    WiFi.softAPConfig(ip, ip, netmask);
    WiFi.softAP(CONFIG_PAGE_SSID, CONFIG_PAGE_PASSWORD);
    servidor.begin();
}

void setup()
{
  display.init();
  drawInitialScreen();
  delay(INITIAL_SCREEN_DURATION);
}

void loop()
{
  drawConfigScreen();
  setupAccessPoint();
  delay(1000);
}