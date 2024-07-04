# Plant Master - Client Web App

## Description

This project is designed to monitor and control plant irrigation using an ESP32 microcontroller. The system includes a React TypeScript application stored in the SPIFFS (SPI Flash File System) of the ESP32, which serves as a user interface accessible via a web browser.

When the ESP32 is connected to the same WiFi network as your device, you can access the web interface at [http://192.168.1.184/](http://192.168.1.184/). This interface provides real-time information about the current humidity levels of your plants, set thresholds, the pins for the humidity sensors, as well as the room's humidity and temperature.

The web application allows users to:

- View current plant humidity levels.
- Set and update humidity thresholds for plants.
- Monitor room humidity and temperature.
- Identify the pins assigned to each humidity sensor.

The React TypeScript application communicates with the ESP32 using WebSockets, ensuring real-time updates and interaction. This setup allows for efficient and immediate responses to changes in the environment, making sure your plants are always well-monitored and watered as needed.

## Features

- **Web Interface**: User-friendly interface built with React TypeScript, accessible on the local network.
- **Real-time Monitoring**: Live updates of plant humidity levels, room humidity, and temperature.
- **Threshold Management**: Set and update humidity thresholds for optimal plant care.
- **Sensor Management**: Information on the pins assigned to each humidity sensor.
- **WebSocket Communication**: Efficient, real-time communication between the web interface and the ESP32.

## Getting Started

To get started, ensure your ESP32 is connected to your WiFi network. Then, navigate to [http://192.168.1.184/](http://192.168.1.184/) in your web browser to access the control panel. From there, you can monitor and control your plant irrigation system with ease.

## Technical Details

- **Microcontroller**: ESP32
- **Web Application**: React TypeScript stored in SPIFFS
- **Communication Protocol**: WebSockets

This system is designed to be simple yet powerful, providing all the tools needed to ensure your plants are properly cared for, with minimal effort required from you.
