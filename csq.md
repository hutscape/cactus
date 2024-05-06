---
layout: csq
title: CSQ
permalink: /csq
sequence: 7

# Lessons
lessons:
  - name: (Prototype) Buy electronics modules for <code>V1.0</code> <em>Make it work, make it right, make it better</em>
  - name: (BOM) Ensure main BOM components are available from vendors before schematic or layout
  - name: (BOM) Check pin, pitch, manufacturer part number, function before buying BOM parts
  - name: (Power) Do a power tree analysis starting with power source before the schematic design
  - name: (Case) Test out paper mockups for mechanical dimensions
  - name: (Case) Do a mechanical consideration before laying out the footprint
  - name: (Schematic) Design a power on/off switch to start/stop using the battery
  - name: (Prototype) Leave out the module's on-board LED as a possible separate indicator E.g. Not linking <code>GPIO02</code> to <code>EN</code> for the shift register
  - name: (Schematic) Don't use main chip's power output to enable other components, use another GPIO pin. E.g. Not linking <code>5V</code> on WeMos to <code>Vin</code> of a sensor or shift register
  - name: (Case) Ensure the mechanical housing has an opening above any environmental sensors E.g humidity, UV index, air pressure
  - name: (Testing) Make 2 units, not just 1 especially for non-interactive projects - one for deployment, one for iteration/testing
  - name: (Chore) Tag the repository with the version number when the PCB is sent out for manufacturing
  - name: (BOM) Reduce total BOM components
  - name: (Power) Increase battery life by cutting off power to the sensors during sleep
  - name: (Firmware) Device an easy way to erase on board WiFi credentials and cloud connectivity details without the need to flash and re-flash the erasing firmware E.g. press a button
  - name: (Chore) Tag the repository with the version number when the PCB is sent out for manufacturing
  - name: (Firmware) Make the measurement interval configurable without re-flashing the firmware

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
