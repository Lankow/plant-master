#include <Arduino.h>

#include "constants.h"
#include "HumidityHandler.h"
#include "WiFiHandler.h"

HumidityHandler humidityHandler(PIN_34, 2000);
WiFiHandler wifiHandler;

void setup() {
  Serial.begin(921600);
  Serial.println("Plant-Master Setup");
  wifiHandler.initWiFi();
}

void loop() {
  delay(1000);
  humidityHandler.readHumidity();
}
