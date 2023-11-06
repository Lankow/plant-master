#include <Arduino.h>
#include <memory> // Include the memory header for std::shared_ptr

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

// Define shared pointers for component instances.
std::shared_ptr<NetworkManager> networkManager = std::make_shared<NetworkManager>();
std::shared_ptr<TimeHandler> timeHandler = std::make_shared<TimeHandler>();
std::shared_ptr<SDCardHandler> sdCardHandler = std::make_shared<SDCardHandler>(EspPins::PIN_18, EspPins::PIN_19, EspPins::PIN_23, EspPins::PIN_5);
std::shared_ptr<HumidityHandler> humidityHandler1 = std::make_shared<HumidityHandler>(EspPins::PIN_34);
std::shared_ptr<HumidityHandler> humidityHandler2 = std::make_shared<HumidityHandler>(EspPins::PIN_35);
std::shared_ptr<TemperatureHandler> temperatureHandler = std::make_shared<TemperatureHandler>(EspPins::PIN_21);
std::shared_ptr<ValveHandler> valveHandler = std::make_shared<ValveHandler>();
std::shared_ptr<PumpHandler> pumpHandler = std::make_shared<PumpHandler>(EspPins::PIN_4);
std::shared_ptr<DataManager> dataManager = std::make_shared<DataManager>();

std::shared_ptr<DataProvider> dataProvider = std::make_shared<DataProvider>();
std::shared_ptr<Logger> logger = std::make_shared<Logger>(sdCardHandler);

// Create an array of shared pointers to components.
std::shared_ptr<Component> components[] = {
    networkManager,
    timeHandler,
    sdCardHandler,
    humidityHandler1,
    humidityHandler2,
    temperatureHandler,
    valveHandler,
    pumpHandler,
    dataManager,
};

void setup()
{
  Serial.begin(921600);
  // Set data provider and logger for each component.
  for (auto &component : components)
  {
    component->setDataProvider(dataProvider);
    component->setLogger(logger);
  }

  // Initialize components.
  for (auto &component : components)
  {
    component->init();
  }
}

void loop()
{
  delay(1000);
  // Trigger cyclic tasks for components.
  for (auto &component : components)
  {
    component->cyclic();
  }
}