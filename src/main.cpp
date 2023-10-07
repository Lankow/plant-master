#include <Arduino.h>

#include "constants.hpp"
#include "handler/HumidityHandler.hpp"
#include "handler/NetworkHandler.hpp"
#include "handler/TimeHandler.hpp"
#include "handler/TemperatureHandler.hpp"
#include "handler/SDCardHandler.hpp"

#include"DataProvider.hpp"

HumidityHandler humidityHandler(PIN_34, 2000);
TemperatureHandler temperatureHandler(PIN_18);
NetworkHandler networkHandler;
TimeHandler timeHandler;
SDCardHandler sdCardHandler(PIN_17, PIN_19, PIN_23, PIN_5);

DataProvider dataProvider(&humidityHandler, &networkHandler, &timeHandler);

void setup() {
  Serial.begin(921600);
  Serial.println("Plant-Master Setup");
  networkHandler.initWiFi();
  networkHandler.initDataProvider(&dataProvider);
  sdCardHandler.initSDCard();
}

void loop() {
  delay(1000);
  humidityHandler.readHumidity();
  temperatureHandler.readTemperature();
  temperatureHandler.readRoomHumidity();
}
