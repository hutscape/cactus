# ariel

> Measure humidity and temperature periodically or on button press

## Development

Run `make install` to add git-secrets and git pre-commit hooks.

## Getting started

1. Connect the hardware according to the instructions in the [firmware](firmware/03-display-humidity-with-led.ino)

    ![](images/protoype-2.JPG)
1. Flash the [firmware](firmware/03-display-humidity-with-led.ino) with the Arduino IDE
1. View the temperature and humidity values on the Arduino serial monitor with baud rate `115200`

    ![](images/serial-2.png)
1. Ensure the bar LEDs are lit accordingly

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

### Similar examples

1. [Shelly H&T is a Battery Powered ESP8266 WiFi Temperature & Humidity Sensor](https://www.cnx-software.com/2018/10/30/shelly-ht-battery-powered-esp8266-wifi-temperature-humidity-sensor/)
