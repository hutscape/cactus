# Firmware

Firmware contains parts of the circuit prototyped and tested separately.

## Development

### Arduino IDE settings

- Board: NodeMCU board ESP-12E
- Flash size: `4M`
- CPU Frequency: `80MHz`
- Upload speed: `115200`
- Port: `/dev/cu.wchusbserial1410`

## Design verification test

Run [`test.ino`](test.ino) to ensure PCB works!

## Main function

- [x] Read humidity from the sensor
- [x] Read temperature from the sensor
- [?] Read battery levels
- [x] Display humidity values in the LEDs
- [ ] Wakeup every 4 hours
- [ ] Wakeup on long button press
- [ ] Check for stored WiFi credentials
- [ ] Connect to WiFi with the stored credentials
- [ ] Setup an AP mode if WiFi cannot be connected
- [ ] Send sensor and battery values to IFTTT if WiFi is connected
- [ ] Wait for 5 minutes in AP mode is WiFi is not connected
- [ ] Sleep after sending data to IFTTT
- [ ] Sleep after waiting for 5 minutes in AP mode

![](test-console.png)
