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

Component* components[] = {
  new SDCardHandler(PIN_17, PIN_19, PIN_23, PIN_5),
  new HumidityHandler(PIN_34),
  new HumidityHandler(PIN_35),
  new TemperatureHandler(PIN_18),
  new TimeHandler,
  new PumpHandler,
  new NetworkManager,
  new DataManager,
};

DataProvider dataProvider;

void setup() {
  Serial.begin(921600);
  Serial.println("Plant-Master Setup");

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
