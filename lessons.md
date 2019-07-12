---
layout: default
title: Lessons learnt
permalink: /lessons
sequence: 9
---
# Lessons Learnt

> Good practices to continue for future projects

- Buy electronics modules for `V1.0` *Make it work, make it right, make it better*
- Ensure main BOM components are available from vendors before schematic or layout
- Check pin, pitch, manufacturer part number, function before buying BOM parts
- Do a power tree analysis starting with power source before the schematic design
- Test out paper mockups for mechanical dimensions
- Do a mechanical consideration before laying out the footprint
- Design a power on/off switch to start/stop using the battery
- Leave out the module's on-board LED as a possible separate indicator E.g. Not linking `GPIO02` to `EN` for the shift register
- Don't use main chip's power output to enable other components, use another GPIO pin. E.g. Not linking `5V` on WeMos to `Vin` of a sensor or shift register
- Ensure the mechanical housing has an opening above any environmental sensors E.g humidity, UV index, air pressure
- Make 2 units, not just 1 especially for non-interactive projects: one for deployment, one for iteration/testing

## V2.0

- No more modules
- Reduce total BOM components
- Do not use ESP8266's LED GPIO pin
- Do not use ESP8266's `5V` pin to power other components
