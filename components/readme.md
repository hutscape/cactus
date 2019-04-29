# Components

## Main components

### Hardware

1. [**`Si7021`** sensor breakout board](https://cdn-learn.adafruit.com/assets/assets/000/035/932/original/temperature_schem.png?1474574583) for temperature and humidity
    - [`Si7021-A20`](https://www.silabs.com/documents/public/data-sheets/Si7021-A20.pdf) - temperature and humidity sensor
    - [`MIC5225-3.3`](https://www.microchip.com/wwwproducts/en/MIC5225) - LDO
    - [`BSS138`](https://www.onsemi.com/pub/Collateral/BSS138-D.PDF) - N-MOSFET
1. [**Shift register**](https://docs-apac.rs-online.com/webdocs/12cd/0900766b812cd41f.pdf) to extend from 1 LED to 5 LEDs
    - [`74HC595`](https://docs-apac.rs-online.com/webdocs/12cd/0900766b812cd41f.pdf) - 8-bit shift register
1. [**WeMos D1 Mini** `V3.0.0`](https://wiki.wemos.cc/_media/products:d1:sch_d1_mini_v3.0.0.pdf)
    - [`ME6211`](https://datasheet.lcsc.com/szlcsc/Nanjing-Micro-One-Elec-ME6211C33M5G-N_C82942.pdf) - LDO
    - [`CH340C`](https://www.mpja.com/download/35227cpdata.pdf) - USB to UART bridge
    - [`W25Q32FVSS`](https://www.winbond.com/resource-files/w25q32fv%20revi%2010202015.pdf) - flash memory
1. [WeMos Battery Shield](https://wiki.wemos.cc/_media/products:d1_mini_shields:sch_battery_v1.3.0.pdf)
    - [`TP5400`](https://datasheet.lcsc.com/szlcsc/Nanjing-Extension-Microelectronics-TP5400_C24154.pdf) - battery management IC

### Firmware

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
1. [IFTTT](ifttt-get): Display humidity in a bar graph LED and send to IFTTT periodically
1. [Wake up with no radio](wakeup-with-no-radio): Wakeup with no radio connectivity to save power consumption
1. [Wake up periodically](wakeup-periodically): Wake up periodically after a specified time
1. [Wake up periodically or on button press](wakeup-periodically-or-button-press): Display and send sensor data to cloud periodically on wake up after deep sleep or by pressing the button on-board

## Parallel experiments

1. [DHT22 sensor](DHT22-sensor): Display humidity and temperature every second with `DHT22` sensor
1. [D flip-flop](d-flip-flop): Test `SN74HC174` Hex D-Type Flip-Flop with Arduino code
1. [Long sleep](long-sleep): Sleep for more than 1 hour using EEPROM
1. [Wakeup after long sleep or on button press](long-sleep-or-button-press)
