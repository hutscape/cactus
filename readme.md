# ariel

> :sweat_drop: Measure humidity and temperature periodically or on button press

## Getting started

1. Connect the hardware according to the instructions in the [firmware](firmware/03-display-humidity-with-led.ino)

    ![](images/protoype-2.JPG)
1. Flash the [firmware](firmware/03-display-humidity-with-led.ino) with the Arduino IDE
1. View the temperature and humidity values on the Arduino serial monitor with baud rate `115200`

    ![](images/serial-2.png)
1. Ensure the bar LEDs are lit accordingly

## Development

### Git secrets

Prevent passwords from being committed

1. Install git secrets

    ```sh
    git secrets --install
    ```
1. Add to `.git/config`

    ```
    [secrets]
      	patterns = ssid\\s=\\s\".*\"
      	allowed = ssid\\s=\\s\"secret\"
      	patterns = password\\s=\\s\".*\"
      	allowed = password\\s=\\s\"secret\"
      	patterns = /trigger/read_humidity/with/key/.*
      	allowed = /trigger/read_humidity/with/key/secret
    ```
1. Check for password with `git secrets --scan -r firmware`
  - Or create a git pre-commit hook

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
