---
layout: default
title: Others
permalink: /others
sequence: 8

# References
references:
  - topic: Similar projects
    list:
      - name: Shelly H&T is a Battery Powered ESP8266 WiFi Temperature & Humidity Sensor
        url: https://www.cnx-software.com/2018/10/30/shelly-ht-battery-powered-esp8266-wifi-temperature-humidity-sensor/

  - topic: ESP8266
    list:
      - name: ESP12-E pinout
        url: https://simba-os.readthedocs.io/en/latest/_images/esp12e-pinout.png
      - name: WeMos D1 mini 2015 schematic
        url: https://escapequotes.net/wp-content/uploads/2016/02/wemos-d1-mini-shematics.jpg
      - name: WeMos D1 mini pinout
        url: http://esp8266-server.de/dateien/wemos/D1-mini-pinoutKl.png

  - topic: Sensor <code>Si7021</code>
    list:
      - name: Si7021 Adafruit Breakout board schematic
        url: https://cdn-learn.adafruit.com/assets/assets/000/035/932/original/temperature_schem.png
      - name: Si7021 SiLabs datasheet
        url: https://www.silabs.com/documents/public/data-sheets/Si7021-A20.pdf
      - name: Adafruit Si7021 Temperature & Humidity Sensor Breakout Board
        url: https://www.adafruit.com/product/3251
      - name: Arduino library for Si7020 and Si7021 environmental sensors
        url: https://github.com/LowPowerLab/SI7021
      - name: MINI Si7021 Temperature and Humidity Sensor
        url: http://www.instructables.com/id/MINI-Si7021-Temperature-and-Humidity-Sensor/
      - name: ESP8266 and Si7021 temperature sensor example
        url: https://www.esp8266learning.com/esp8266-si7021-temperature-sensor-example.php

  - topic: Shift register <code>SN74HC595</code>
    list:
      - name: SN74HC595 TI datasheet
        url: http://www.ti.com/lit/ds/symlink/sn74hc595.pdf
      - name: 74HC595 pinout
        url: https://learn.pimoroni.com/static/repos/learn/170pt-projects/pinout-74hc595.jpg

  - topic: Coin cell
    list:
      - name: Shelly H&T is a Battery Powered ESP8266 WiFi Temperature & Humidity Sensor
        url: https://www.cnx-software.com/2018/10/30/shelly-ht-battery-powered-esp8266-wifi-temperature-humidity-sensor/
      - name: ESP8266 Sensor runs 17 days on a coin cell
        url: https://www.youtube.com/watch?v=IYuYTfO6iOs
      - name: How to build an open WiFi finder using ESP8266 and two coin batteries
        url: https://medium.com/@kstevica/how-to-build-an-open-wifi-finder-using-esp8266-and-two-coin-batteries-9c31eb6f9859
      - name: How to Run Your ESP8266 for Years on a Battery
        url: https://openhomeautomation.net/esp8266-battery/

  - topic: Battery shield
    list:
      - name: WeMos battery shield
        url: https://arduinodiy.wordpress.com/2017/01/02/reviewing-the-wemos-battery-shield
      - name: Power usage of WeMos and battery shield
        url: http://harald.studiokubota.com/wordpress/index.php/2016/08/20/power-usage-of-wemos-d1-mini-ws2812b-rgb-shield
      - name: Battery shield docs and schematic
        url: https://wiki.wemos.cc/products:d1_mini_shields:battery_shield
      - name: WeMos lithium battery shield
        url: https://www.youtube.com/watch?v=z6Vgy1cY0XU
      - name: Monitoring LiPo battery voltage with Wemos D1 minibattery shield and Thingspeak
        url: https://arduinodiy.wordpress.com/2016/12/25/monitoring-lipo-battery-voltage-with-wemos-d1-minibattery-shield-and-thingspeak/

  - topic: Programming
    list:
      - name: ESP8266 pogo jig programming
        url: https://hackaday.io/project/20046-esp8266-pogo-jig-programming-board

  - topic: Design tools
    list:
      - name: Creating an FPGA Power Tree
        url: https://www.intel.com/content/dam/www/programmable/us/en/pdfs/literature/an/an-721-creating-fpga-power-tree.pdf
      - name: System-Level Design Tool Quick Start Guide
        url: https://www.analog.com/media/en/technical-documentation/user-guides/ltpowerplanneriii_qsg.pdf

  - topic: Low power
    list:
      - name: ESP8266 Low Power Solutions
        url: https://www.espressif.com/sites/default/files/9b-esp8266-low_power_solutions_en_0.pdf
      - name: ESP8266 Maximum deep sleep i ~71 minutes
        url: https://www.losant.com/blog/making-the-esp8266-low-powered-with-deep-sleep
      - name: Extend ESP8266 12 F Deep Sleep Time
        url: https://electronics.stackexchange.com/questions/306374/extend-esp8266-12-f-deep-sleep-time

# Lessons
lessons:
  - title: Lessons learnt
    subtitle: Good practices to continue for future projects
    list:
      - name: Buy electronics modules for <code>V1.0</code> <em>Make it work, make it right, make it better</em>
      - name: Ensure main BOM components are available from vendors before schematic or layout
      - name: Check pin, pitch, manufacturer part number, function before buying BOM parts
      - name: Do a power tree analysis starting with power source before the schematic design
      - name: Test out paper mockups for mechanical dimensions
      - name: Do a mechanical consideration before laying out the footprint
      - name: Design a power on/off switch to start/stop using the battery
      - name: Leave out the module's on-board LED as a possible separate indicator E.g. Not linking <code>GPIO02</code> to <code>EN</code> for the shift register
      - name: Don't use main chip's power output to enable other components, use another GPIO pin. E.g. Not linking <code>5V</code> on WeMos to <code>Vin</code> of a sensor or shift register
      - name: Ensure the mechanical housing has an opening above any environmental sensors E.g humidity, UV index, air pressure
      - name: Make 2 units, not just 1 especially for non-interactive projects - one for deployment, one for iteration/testing
      - name: Tag the repository with the version number when the PCB is sent out for manufacturing
  - title: V2.0
    subtitle: For next iteration
    list:
      - name: No more modules
      - name: Reduce total BOM components
      - name: Do not use ESP8266's LED GPIO pin
      - name: Do not use ESP8266's <code>5V</code> pin to power other components
      - name: Increase battery life by cutting off power to the sensors during sleep
      - name: Device an easy way to erase on board WiFi credentials and cloud connectivity details without the need to flash and re-flash the erasing firmware E.g. press a button
      - name: Tag the repository with the version number when the PCB is sent out for manufacturing
      - name: Make the measurement interval configurable without re-flashing the firmware

# Schedule
design_start: '2019-03-12'
design_end: '2019-03-29'
manufacturing_start: '2019-04-04'
manufacturing_end: '2019-04-12'
integration_start: '2019-04-15'
integration_end: '2019-05-06'
deployment_start: '2019-05-06'
deployment_end: '2019-05-09'

---
