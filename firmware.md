---
layout: default
title: Firmware
permalink: /firmware
sequence: 3
---

# Firmware

Firmware contains parts of the circuit prototyped and tested separately.

## Arduino IDE settings

- Board: NodeMCU board ESP-12E
- Flash size: `4M`
- CPU Frequency: `80MHz`
- Upload speed: `115200`
- Port: `/dev/cu.wchusbserial1410`

## Main features

- [x] Read humidity from the sensor
- [x] Read temperature from the sensor
- [x] Read battery levels
- [x] Display humidity values in the LEDs
- [x] Wakeup every 4 hours
- [x] Wakeup on long button press
- [x] Check for stored WiFi credentials
- [x] Connect to WiFi with the stored credentials
- [x] Setup an AP mode if WiFi cannot be connected
- [x] Send sensor and battery values to IFTTT if WiFi is connected
- [x] Wait for 5 minutes in AP mode is WiFi is not connected
- [x] Sleep after sending data to IFTTT
- [x] Sleep after waiting for 5 minutes in AP mode
