#include <Arduino.h>

#include "constants.hpp"
#include "DataProvider.hpp"

#include "handler/HumidityHandler.hpp"
#include "handler/TimeHandler.hpp"
#include "handler/TemperatureHandler.hpp"
#include "handler/SDCardHandler.hpp"
#include "handler/PumpHandler.hpp"

#include "manager/NetworkManager.hpp"
#include "manager/DataManager.hpp"

Handler* handlers[] = {
  new SDCardHandler(PIN_17, PIN_19, PIN_23, PIN_5),
  new HumidityHandler(PIN_34),
  new HumidityHandler(PIN_35),
  new TemperatureHandler(PIN_18),
  new TimeHandler,
  new PumpHandler(),
};

DataProvider dataProvider;

NetworkManager networkManager(&dataProvider);
DataManager dataManager(&dataProvider);

void setup() {
  Serial.begin(921600);
  Serial.println("Plant-Master Setup");
  networkManager.init();

  // Handlers Initialization
  for (int i = 0; i < sizeof(handlers) / sizeof(handlers[0]); i++) {
    handlers[i]->init();
  }

  // Handlers subscription to DataProvider
  for (int i = 0; i < sizeof(handlers) / sizeof(handlers[0]); i++) {
    handlers[i]->subscribeDataProvider(&dataProvider);
  }
}

void loop() {
  delay(1000);

  // Triggering Cyclic Tasks for Handlers
  for (int i = 0; i < sizeof(handlers) / sizeof(handlers[0]); i++) {
    handlers[i]->cyclic();
  }
}
