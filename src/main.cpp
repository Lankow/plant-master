#include <Arduino.h>

#include "constants.h"
#include "HumidityHandler.h"
#include "NetworkHandler.h"
#include "TimeHandler.h"

HumidityHandler humidityHandler(PIN_34, 2000);
NetworkHandler networkHandler;
TimeHandler timeHandler;

void setup() {
  Serial.begin(921600);
  Serial.println("Plant-Master Setup");
  networkHandler.initWiFi();
}

void loop() {
  delay(1000);
  humidityHandler.readHumidity();
  timeHandler.getTimeStamp();
  networkHandler.handleClient();
}
