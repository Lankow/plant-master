#include <Arduino.h>
#include <Wire.h>  
#include "SSD1306Wire.h"
#include "OLEDDisplayUi.h"
#define INITIAL_SCREEN_DURATION 3000

SSD1306Wire display(0x3c, SDA, SCL); 

void drawInitialScreen()
{
  display.clear();
  display.drawString(30, 10, "Plant-Master");
  display.drawHorizontalLine(10, 26, 100);
  display.drawString(35, 30, "by Lankow");
  display.display();
}

void setup()
{
  display.init();
  drawInitialScreen();
  delay(INITIAL_SCREEN_DURATION);
}

void loop()
{
  display.clear();
  display.display();

  delay(1000);
}