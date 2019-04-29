# Long sleep

> Sleep for more than 1 hour using EEPROM to keep the count

## Hardware

- nodeMCU to button for interrupt
- Short pin `D0` to pin RST
- Un-short the 2 pins above during uploading firmware

## Firmware

Upload [firmware](long-sleep.ino) with Arduino
