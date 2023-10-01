#include <Arduino.h>

#include "constants.hpp"
#include "handler/HumidityHandler.hpp"
#include "handler/NetworkHandler.hpp"
#include "handler/TimeHandler.hpp"

#include"DataProvider.hpp"

HumidityHandler humidityHandler(PIN_34, 2000);
NetworkHandler networkHandler;
TimeHandler timeHandler;

DataProvider dataProvider(&humidityHandler, &networkHandler, &timeHandler);

void setup() {
  Serial.begin(921600);
  Serial.println("Plant-Master Setup");
  networkHandler.initWiFi();
  networkHandler.initDataProvider(&dataProvider);
}

void loop() {
  delay(1000);
  humidityHandler.readHumidity();
}
