/**
 * @file PlantMaster.cpp
 * @date   2024-05-31
 * @author Lankow
 * @version 1.0
 *
 * @brief This file contains the implementation of the PlantMaster class.
 *
 * The PlantMaster class is responsible for initializing and managing the core components
 * of the Plant Master system, including network initialization, data handling, and
 * managing various sensors and controllers.
 */
#include "PlantMaster.hpp"

PlantMaster::PlantMaster(std::shared_ptr<Configurator> configurator)
    : m_isInitialized(false),
      m_wiFiInitializer(),
      m_resetHandler(),
      m_configurator(std::move(configurator)),
#ifdef PLANT_MASTER
      m_dataStorage(std::make_shared<DataStorage>(m_configurator)),
      m_dataHandler(std::make_shared<DataHandler>(m_dataStorage)),
      m_serverManager(m_dataStorage),
      m_mqttManager(std::make_shared<MQTTManager>(m_dataHandler, m_configurator)),
      m_wateringManager(m_dataStorage, m_mqttManager),
      m_displayRenderer(m_configurator)
#else
      m_dataStorage(std::make_shared<DataStorage>()),
      m_dataHandler(std::make_shared<DataHandler>(m_dataStorage)),
      m_mqttManager(std::make_shared<MQTTManager>(m_dataHandler)),
      m_dhtReader(m_configurator, m_mqttManager),
      m_plantHumidityHandler(m_configurator, m_mqttManager, m_dataStorage),
      m_waterPumpController(m_configurator, m_dataStorage)
#endif
{
}

bool PlantMaster::init()
{
#ifdef PLANT_MASTER
    m_displayRenderer.drawInitialScreen();
    m_displayRenderer.drawResetScreen();
#endif

    if (!m_wiFiInitializer.init())
    {
        Serial.println("Failed to initialize WiFi");
        return false;
    }

    Serial.println("Connected to WiFi successfully.");
    m_mqttManager->init();
    m_resetHandler.init();

#ifdef PLANT_MASTER
    m_serverManager.init();
#else
    m_waterPumpController.init();
    m_dhtReader.init();
#endif

    m_isInitialized = true;
    return true;
}

void PlantMaster::cyclic()
{
    m_resetHandler.cyclic();

    if (m_isInitialized)
    {
        m_mqttManager->cyclic();
#ifdef PLANT_MASTER
        m_serverManager.cyclic();
        m_wateringManager.cyclic();
#else
        m_dhtReader.cyclic();
        m_plantHumidityHandler.cyclic();
#endif
    }
}
