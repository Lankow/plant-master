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
  new NetworkManager,
  new TimeHandler,
  new SDCardHandler(PIN_18, PIN_19, PIN_23, PIN_5),
  new HumidityHandler(PIN_34),
  new HumidityHandler(PIN_35),
  new TemperatureHandler(PIN_21),
  new ValveHandler,
  new PumpHandler,
  new DataManager,
};

DataProvider dataProvider;
Logger logger(static_cast<SDCardHandler*>(components[1]));

void setup() {
  Serial.begin(921600);
  // Components Initialization
  for (int i = 0; i < sizeof(components) / sizeof(components[0]); i++) {
    components[i]->subscribeDataProvider(&dataProvider);
    components[i]->init();
  }
}

void loop() {
  delay(1000);
  // Triggering Cyclic Tasks for Components
  for (int i = 0; i < sizeof(components) / sizeof(components[0]); i++) {
    components[i]->cyclic();
  }
}
