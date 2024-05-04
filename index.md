---
layout: start
title: Start
permalink: /
sequence: 1

manufacturing: true
downloads:
  code: true
  schematic: true
  layout: true
  kicad: true
  gerber: true
  bom: true
  freecad: false
  case: false
software:
  - name: Demo firmware
    code: _code/demo

features:
  - detail: Read humidity and temperature values from the sensor <code>Si7021</code>
  - detail: Read LiPo battery levels
  - detail: Display the current humidity value through the on-board LEDs
  - detail: Wakeup every <code>6 hours</code> or on button press to read the sensor and send data to the cloud
  - detail: Sleep after sending data to IFTTT
  - detail: Check for stored WiFi credentials upon waking up and connect back to the store WiFi
  - detail: Connect to WiFi with the stored credentials
  - detail: Setup an AP mode if WiFi cannot be connected
  - detail: Send sensor and battery values to IFTTT if WiFi is connected
  - detail: Wait for <code>5 minutes</code> in AP mode is WiFi is not connected
  - detail: Sleep after waiting for <code>5 minutes</code> in AP mode
  - detail: Charge the LiPo by plugging in the USB cable into the battery shield
firmware_instructions: Use firmware version at least <a href="https://github.com/esp8266/Arduino/tree/0da6906499aaa9977f7b456c6ec32c090b117cef">Arduino ESP8266 commit hash <code>0da69064</code></a> and above for mDNS patch.
---

## Maintenance

⚠️ **USB Connectors on WeMos D1 Mini vs WeMos battery shield**
- Do not plug in the USB cable on WeMos D1 Mini while the battery shield is on the PCB
- **Flashing firmware**: Remove the battery shield from the PCB and use the USB cable on the WeMos D1 mini

Charge the LiPo by plugging in the USB cable into the battery shield
