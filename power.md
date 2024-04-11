---
layout: power
title: Power
permalink: /power
sequence: 6

# Power
power:
  tree: true
  components: true
  calculation: true
  source: <code>2000mAh</code> LiPo battery
  battery_life: 1 month
  charging_duration: 12 hours
  charging_instruction: Remove the WeMos Battery shield from the board. Plug in the USB cable to the WeMos battery shield to charge. <code>Red</code> LED will be on while it is charging.<code>Green</code> LED will be on when charging is complete.
---

# Power consumption of main components

| Chip # | Chip | Operating Voltage | Active mode | Modem-sleep mode | Deep-sleep mode | Total |
|-----------|-----------|---------|-------------|-----------|------------|---------|
| ESP8266 | WiFi based MCU | 3.3V | 170mA | 15mA   | 10uA  | |
| Si7021 | Temperature / Humidity sensor | 1.9V - 3.6V | 150uA  | | 60nA  | |
| SN4HC595 | Shift register | 2V - 6V | 60uA | | 1uA  | |
| Total consumption | | | 170.23mA | 15mA | 11.06uA| |

- Total duration: `30s.`
- Total duration in Modem-sleep mode: 10s x 12 = `120s.`
- Total duration in Deep-sleep mode: `4h.`
- Total charge in Active mode: 30/14400 * 170.21m = `0.354 mAs`
- Total charge in Modem-sleep mode: 120/14400 * 15m = `0.125mAs`
- Total charge in Deep-sleep mode: 14250/14400 * 11.06u = `0.011mAs`
- Total charge: `0.589mAs`

# Power calculation

3 power modes:

1. Wakes up in **Active mode** for 30 seconds every 4 hours to read the sensor value and ping to cloud
1. Wakes up in **Mode-sleep mode** for **10 seconds** every **20 minutes** to check whether the counter has reached the threshold
1. **Deep-sleep mode** for the rest of the time, unless user button pressed

`1200mAh` battery will last for `(1200/24/30)` = **2.89 months**

# Measuring power

| Mode | Pins | Voltage |
|------|------|---------|
| Deep sleep | `5V` - `GND` on WeMos D1 mini | `4.94V` |
| Deep sleep | `Vin` - `GND` on Si7021 breakout board | `5V` |
| Deep sleep | `Vcc` - `GND` on 74HC595 chip | `5V` |
| Deep sleep | `EN` - `GND` on 74HC595 chip | |

## Actual vs. calculated power

| Periodic wakeup | Calculated | Actual | Error % |
|-----------------|------------|--------|---------|
| 6 hours         | 2.89 months| 30 days| ~300% ⁉️ |
