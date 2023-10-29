#include <Arduino.h>
#include "constants.hpp"
#include "DataProvider.hpp"
#include "Component.hpp"
#include "Logger.hpp"
#include "handler/HumidityHandler.hpp"
#include "handler/TimeHandler.hpp"
#include "handler/TemperatureHandler.hpp"
#include "handler/SDCardHandler.hpp"
#include "handler/PumpHandler.hpp"
#include "handler/ValveHandler.hpp"
#include "manager/NetworkManager.hpp"
#include "manager/DataManager.hpp"

// Define component instances as global variables (stack-allocated).
NetworkManager networkManager;
TimeHandler timeHandler;
SDCardHandler sdCardHandler(PIN_18, PIN_19, PIN_23, PIN_5);
HumidityHandler humidityHandler1(PIN_34);
HumidityHandler humidityHandler2(PIN_35);
TemperatureHandler temperatureHandler(PIN_21);
ValveHandler valveHandler;
PumpHandler pumpHandler;
DataManager dataManager;

DataProvider dataProvider;
Logger logger(&sdCardHandler);

Component *components[] = {
    &networkManager,
    &timeHandler,
    &sdCardHandler,
    &humidityHandler1,
    &humidityHandler2,
    &temperatureHandler,
    &valveHandler,
    &pumpHandler,
    &dataManager,
};

void setup()
{
  Serial.begin(921600);
  // Subscribe data provider and logger for each component.
  for (Component *component : components)
  {
    component->setDataProvider(&dataProvider);
    component->setLogger(&logger);
  }

  // Initialize components.
  for (Component *component : components)
  {
    component->init();
  }
}

void loop()
{
  delay(1000);
  // Trigger cyclic tasks for components.
  for (Component *component : components)
  {
    component->cyclic();
  }
}