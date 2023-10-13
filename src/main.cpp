#include <Arduino.h>

#include "constants.hpp"
#include "DataProvider.hpp"

#include "Logger.hpp"

#include "handler/HumidityHandler.hpp"
#include "handler/TimeHandler.hpp"
#include "handler/TemperatureHandler.hpp"
#include "handler/SDCardHandler.hpp"
#include "handler/PumpHandler.hpp"
#include "handler/ValveHandler.hpp"

#include "manager/NetworkManager.hpp"
#include "manager/DataManager.hpp"

Component* components[] = {
  new SDCardHandler(PIN_18, PIN_19, PIN_23, PIN_5),
  new HumidityHandler(PIN_34),
  new HumidityHandler(PIN_35),
  new TemperatureHandler(PIN_21),
  new TimeHandler,
  new ValveHandler,
  new PumpHandler,
  new NetworkManager,
  new DataManager,
};

Logger logger(components[0]);
DataProvider dataProvider;

void setup() {
  Serial.begin(921600);
  Logger::log("Plant-Master Setup");

  // Handlers Initialization
  for (int i = 0; i < sizeof(components) / sizeof(components[0]); i++) {
    components[i]->init();
  }

  // Handlers subscription to DataProvider
  for (int i = 0; i < sizeof(components) / sizeof(components[0]); i++) {
    components[i]->subscribeDataProvider(&dataProvider);
  }
}

void loop() {
  delay(1000);

  // Triggering Cyclic Tasks for Handlers
  for (int i = 0; i < sizeof(components) / sizeof(components[0]); i++) {
    components[i]->cyclic();
  }
}
