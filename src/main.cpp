#include <Arduino.h>
#include <Wire.h>  
#include "SSD1306Wire.h"
#include "OLEDDisplayUi.h"

SSD1306Wire display(0x3c, SDA, SCL); 
  
void setup()
{
  display.init();
  display.clear();
  display.drawString(30, 30, "Plant-Master");
  display.display();
}

void loop()
{
  delay(1000);
}