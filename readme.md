# hippo

> measure temperature and humidity periodically

## Getting started

1. Connect [Si7021](https://www.adafruit.com/product/3251) breakout board and [WeMos nodeMCU](https://www.wemos.cc/product/d1-mini-pro.html)
  - `VIN` on si7021 and `3V3` on nodeMCU
  - `GND` on si7021 and `G` on nodeMCU
  - `SDA` on si7021 and `D3` on nodeMCU
  - `SCL` on si7021 and `D4` on nodeMCU
1. Flash the [firmware](firmware/main.ino)
1. View the temperature and humidity values on the Arduino serial monitor with baud rate `115200`

## References 📚

### Sensor Si7021

1. [Adafruit Si7021 Temperature & Humidity Sensor Breakout Board](https://www.adafruit.com/product/3251)
1. [Arduino library for SI7020 and SI7021 environmental sensors](https://github.com/LowPowerLab/SI7021)
1. [MINI Si7021 Temperature and Humidity Senso](http://www.instructables.com/id/MINI-Si7021-Temperature-and-Humidity-Sensor/)
1. [ESP8266 and Si7021 temperature sensor example](https://www.esp8266learning.com/esp8266-si7021-temperature-sensor-example.php)

### ESP8266 on Coin Cell

1. [ESP8266 Sensor runs 17 days on a coin cell](https://www.youtube.com/watch?v=IYuYTfO6iOs)
1. [How to build an open WiFi finder using ESP8266 and two coin batteries](https://medium.com/@kstevica/how-to-build-an-open-wifi-finder-using-esp8266-and-two-coin-batteries-9c31eb6f9859)
1. [How to Run Your ESP8266 for Years on a Battery](https://openhomeautomation.net/esp8266-battery/)
