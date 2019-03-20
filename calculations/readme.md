# Calculations

## Main components

| Chip # | Chip | Operating Voltage | Active mode | Standby / Sleep mode |
| ------ | ------ | ------ | ------ | ------ |
| SN4HC595 | Shift register | 2V - 6V | 80uA | 1uA |
| Si7021 | Temperature / Humidity sensor | 1.9V - 3.6V | 150uA | 60nA |
| ESP8266 | WiFi based MCU | 3.3V | 170mA | 10uA |
| **Total consumption** | | | **170.23mA** | **11.06uA** |
| **Total duration** | | | **30s.** | **4h.** |

`30/14400 * 170.23m + 14370/14400 * 11.06u = 0.3656mA`

- `2000mAh` battery will last for `5470 hours ≃ 7.59 months`
- `500mAh` battery will last for `1402 h ≃ 60 days`
