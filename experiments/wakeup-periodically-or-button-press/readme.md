# Wake up periodically or on button press

Send sensor data to cloud periodically or by pressing the button on-board.

## Firmware [[link](main.ino)]

Features:

- Wakeup the ESP8266 periodically without any WiFi to save battery
- Increment the interval count on the RTC memory
- Connect to WiFi and so something only if the interval count of the wakeup is correct
