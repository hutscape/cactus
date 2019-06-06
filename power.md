# Power

## Power source

`1200mAh` LiPo

## Main components

| Chip # | Chip | Operating Voltage | Active mode | Modem-sleep mode | Deep-sleep mode |
| ------ | ------ | ------ | ------ | ------ | ------ |
| ESP8266 | WiFi based MCU | `3.3V` | `170mA` | `15mA` | `10uA` |
| Si7021 | Temperature / Humidity sensor | `1.9V` - `3.6V` | `150uA` |  | `60nA` |
| SN4HC595 | Shift register | `2V` - `6V` | `60uA` |  | `1uA` |
| **Total consumption** | | | **170.23mA** | **15mA** | **11.06uA** |
| **Total duration** | | | **30s.** | 10s x 12 = **120s.** |**4h.** |

## Calculated

3 power modes:

- Wakes up in **Active mode** for **30 seconds** every **4 hours** to read the sensor value and ping to cloud
- Wakes up in **Mode-sleep mode** for **10 seconds** every **20 minutes** to check whether the counter has reached the threshold
- **Deep-sleep mode** for the rest of the time, unless user button pressed

```
30/14400 * 170.21m 				--> Active mode
+ 120/14400 *15m					--> Modem-sleep mode
+ 14250/14400 * 11.06u 		--> Deep-sleep mode

=
0.354 mAs
+ 0.125mAs
+ 0.011mAs

= 0.589 mAs
```

`1200mAh` battery will last for `1200/0.589/24/30 = 2.89 months`

## Measuring

| Mode | Pins | Voltage
| ------ | ------ | ------ |
| Deep sleep | `5V` - `GND` on WeMos D1 mini | `4.94V`
| Deep sleep | `Vin` - `GND` on Si7021 breakout board | `5V`
| Deep sleep | `Vcc` - `GND` on 74HC595 chip | `5V`
| Deep sleep | `EN` - `GND` on 74HC595 chip |

## Actual vs Calculated

| Periodic wakeup | Calculated | Actual | Error %
| ------ | ------ | ------ | ------ |
| 6 hours | 2.89 months | 10 days | 767% ⁉️

## Charging

Takes about 12 hours to re-charge to 100%.

## References

- [ESP8266 Low Power Solutions](https://www.espressif.com/sites/default/files/9b-esp8266-low_power_solutions_en_0.pdf)
- [ESP8266 Maximum deep sleep i ~71 minutes](https://www.losant.com/blog/making-the-esp8266-low-powered-with-deep-sleep)
- [Extend ESP8266 12 F Deep Sleep Time](https://electronics.stackexchange.com/questions/306374/extend-esp8266-12-f-deep-sleep-time)
