# DHT22

Display humidity and temperature every second with `DHT22` sensor

## Hardware

Hardware: nodeMCU with DHT22 (with square holes facing you)
- left most pin on DHT22 and `3V3` on nodeMCU
  (requires clean 3.3V or even higher at 5V)
- second left most pin on DHT22 and `D2` on nodeMCU
- third left most pin on DHT22 is not connected
- right most pin on DHT22 is connected to `GND`
- add 10k resistor between left most pin and second left most pin

## Firmware

With [Arduino code](main.ino)

## Reference

- [DHT-sensor-library](https://github.com/adafruit/DHT-sensor-library/blob/master/examples/DHTtester/DHTtester.ino) from Adafruit
