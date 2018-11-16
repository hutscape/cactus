# Experiments

## Main components

1. **`Si7021`** sensor for temperature and humidity
1. **Shift register** to extend from 1 PED to 5 LEDs
1. **RTC Memory** on ESP8266 to count long sleep intervals
1. **IFTTT** for cloud connectivity on wakeup
1. Wake up after deep sleep with no radio to save power
1. Wake up on button press

## Component experiments

Hardware and firmware components to build up to the entire project

1. [Sensor Si7921](sensor-si7021): Display humidity and temperature every frequency with `Si7921` sensor
1. [Shift register](shift-register): Display LED as a bar graph going from 1 LED ON to all 5 LEDs ON
1. [Display humidity with LED](display-humidity-with-led): Display humidity in a bar graph LED
1. [RTC Memory](rtc-memory): Use RTC memory in ESP8266 because it survives deep sleep mode to reduce power consumption even further
1. [IFTTT](ifttt): Display humidity in a bar graph LED and send to IFTTT periodically
1. [Wake up with no radio](wakeup-with-no-radio): Wakeup with no radio connectivity to save power consumption
1. [Wake up periodically or on button press](wakeup-periodically-or-button-press)

## Parallel experiments

1. [DHT22 sensor](DHT22-sensor): Display humidity and temperature every second with `DHT22` sensor
1. [D flip-flop](d-flip-flop): test `SN74HC174` Hex D-Type Flip-Flop with Arduino code
1. [Long sleep](long-sleep): Sleep for more than 1 hour using EEPROM
1. [Wakeup after long sleep or on button press](long-sleep-or-button-press
