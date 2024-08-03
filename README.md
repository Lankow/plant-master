# Plant-Master: Home Plant Monitoring and Watering System

**Plant-Master** is a home plant monitoring and watering system. The project is divided into two variants:

- **Plant-Master**: Aggregates data, hosts a React application, MQTT broker, and communicates with the user via an SSD1306 display.
- **Plant-Monitor**: Connects soil moisture sensors, temperature and humidity sensors, and controls water valves and a pump.

## Setup Instructions

### Initial WiFi Configuration

Upon first startup, both Plant-Master and Plant-Monitor require WiFi credentials:

1. Each device will create an Access Point named:
   - `plant-master-config` with password `plantmaster`
   - `plant-monitor-config` with password `plantmonitor`
2. Connect to the respective WiFi network and provide the SSID and password of your local WiFi network.
3. If the credentials are correct, the device will restart and begin functioning.
4. SSID and password will be saved in NVM. To reset to initial settings and clear NVM, hold the Boot button for 10 seconds.

### Operational Cycles

- **Plant-Master**: Collects data via MQTT from Plant-Monitor, compares soil moisture against set thresholds, and sends commands to Plant-Monitor to activate water valves and pump if necessary.
- **Plant-Monitor**: Reads which valve to open and if the pump should be active, sends plant watering status via MQTT.

### Hosted Application

- Plant-Master hosts a React application for managing plant thresholds and viewing data received from Plant-Monitor.
- The application is written in TypeScript and React, located in the `plant-master-client` directory.
  - `npm run dev`: Runs the application locally in development mode.
  - `npm run build`: Builds and compresses the application into the `data` folder, which is then uploaded to the board as a Filesystem Image.

Demo available at: [Plant-Master Demo](https://lankow.github.io/plant-master/)

## Configuration

### `config.json`

The `config.json` file is processed by the `prepare_config.py` script during the build to suit the hardware requirements of Plant-Master or Plant-Monitor.

Example configuration:

```json
{
  "dhtPin": 21,
  "oledMosiPin": 23,
  "oledClkPin": 18,
  "oledDcPin": 17,
  "oledCsPin": 5,
  "oledResetPin": 16,
  "waterPumpPin": 18,
  "readerPins": [34, 33, 32],
  "valvePins": [15, 14, 17],
  "thresholds": [500, 2050, 1000]
}
```

Customize based on your hardware and pin connections.

### Requirements

- **Software**:

  - VSCode as IDE
  - PlatformIO
  - NodeJS for the web application

- **Hardware**:
  - At least two ESP32 boards: one for Plant-Master, others for Plant-Monitors
  - One SSD1306 display
  - One DHT sensor
  - One or more soil moisture sensors (e.g., DFRobot)

## Build and Upload Instructions

### Using VSCode Buttons

Preconfigured buttons in VSCode for building and uploading:

- **Build**:
  - Plant-Master: `Build Plant-Master`
  - Plant-Monitor: `Build Plant-Monitor`
- **Upload**:
  - Plant-Master: `Upload Plant-Master`
  - Plant-Monitor: `Upload Plant-Monitor`

### Using Commands

#### Plant-Master

- Build: `pio run -e plant-master -a 'runExtraScripts'`
- Upload: `pio run -e plant-master -t nobuild -t upload`
- Upload Filesystem Image (web app and config): `pio run -e plant-master -t uploadfs`

#### Plant-Monitor

- Build: `pio run -e plant-monitor -a 'runExtraScripts'`
- Upload: `pio run -e plant-monitor -t nobuild -t upload`
- Upload Filesystem Image (config only): `pio run -e plant-monitor -t uploadfs`
