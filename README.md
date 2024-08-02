# Plant-Master - Plant Monitoring and Control System

This project is a Plant Monitoring and Control System split into two main components: the "Monitor" and the "Master." These components interact with each other via MQTT to manage and monitor plant conditions, such as humidity levels, and control the water pump system.

## Getting Started

### Software Prerequisites

- PlatformIO
- Visual Studio Code (recommended for PlatformIO IDE)
- NodeJS

### Hardware Prerequisites

- ESP32
- SSD1306 Display
- DHT Sensor
- Soil Humidity Sensor

### Setting Up the Environment

1. **Clone the repository:**

   ```sh
   git clone https://github.com/Lankow/plant-master.git
   cd plant-master
   ```

2. **Install PlatformIO:**
   Follow the instructions on the PlatformIO website to install PlatformIO.

3. **Open the project in Visual Studio Code:**

4. **Install dependencies:**
   PlatformIO will automatically install the necessary libraries specified in platformio.ini when you open the project.

### PlatformIO Configuration

Ensure your `platformio.ini` file includes the necessary configurations:

### Plant-Master Configuration

## Running the Project

Modify `config.json` in order to map pin assignment of hardware.

```sh
{
   "dhtPin": 21,
   "oledMosiPin": 23,
   "oledClkPin": 18,
   "oledDcPin": 17,
   "oledCsPin": 5,
   "oledResetPin": 16,
   "waterPumpPin": 18,
   "readerPins": [34 33, 32],
   "valvePins": [15, 14, 17],
   "thresholds": [500, 2050, 1000]
}
```

1. **Build the Plant-Master:**

```sh
pio run -e plant-master -a 'runExtraScripts' #Plant-Master variant
pio run -e plant-monitor -a 'runExtraScripts' #Plant-Monitor variant
```

2. **Upload application to your device:**

```sh
pio run -e plant-master -t nobuild -t upload #Plant-Master variant
pio run -e plant-monitor -t nobuild -t upload #Plant-Monitor variant
```

2. **Upload Filesystem Image to your device:**

```sh
pio run -e plant-master -t uploadfs #Plant-Master variant
pio run -e plant-monitor -t uploadfs #Plant-Monitor variant
```

3. **Monitor the serial output:**

```sh
pio device monitor
```

## Client Application Demo:

Hosted React Application Demo: [lankow.github.io/plant-master/](https://lankow.github.io/plant-master/).
