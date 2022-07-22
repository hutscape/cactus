---
layout: start
title: Getting Started
permalink: /
sequence: 1

manufacturing: true
downloads:
  schematic: true
  layout: true
  kicad: true
  gerber: true
  bom: true
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

<section class="section is-small">
  <div class="container">
    <h2 class="title is-1">Getting Started</h2>

    <div class="tile is-ancestor">
      <div class="tile is-vertical is-12">
        <div class="tile">
          <div class="tile is-parent">
            <article class="tile is-child notification">
              <p class="title">Step 1</p>
              <p class="subtitle">Setup an <a href="https://ifttt.com/services/maker_webhooks">IFTTT webhook</a> to receive a POST request with data and add a row to a Google Spreadsheet.</p>
              <a href="{{ site.url }}/images/start/ifttt.png"><img src="{{ site.url }}/images/start/ifttt.png" alt="IFTTT"></a>
            </article>
          </div>
          <div class="tile is-parent">
            <article class="tile is-child notification">
              <p class="title">Step 2</p>
              <p class="subtitle">Connect to the WiFi access point <code>Cactus {UNIQUE_MAC_ADDRESS}</code>.</p>
              <p class="subtitle">Go to the web page <code>http://cactus.local</code> to fill in the WiFi credentials and <a href="https://ifttt.com/services/maker_webhooks/settings">IFTTT webhook key</a>.</p>
              <a href="{{ site.url }}/images/start/access_point.jpg"><img src="{{ site.url }}/images/start/access_point.jpg" alt="Access point"></a>
              <a href="{{ site.url }}/images/start/webpage.png"><img src="{{ site.url }}/images/start/webpage.png" alt="Webpage form"></a>
            </article>
          </div>
          <div class="tile is-parent">
            <article class="tile is-child notification">
              <div class="content">
                <p class="title">Step 3</p>
                <p class="subtitle">Press on-board button or wait for the <a href="https://docs.google.com/spreadsheets/d/1qedLXiCeU6vCwEvv3JqwrVWjrriB8L3DA9Xp-g01Jk0/edit?usp=sharing">Google Sheet</a> to update with a new row with a periodic update to the cloud.</p>
                <a href="{{ site.url }}/images/start/google-sheet.png"><img src="{{ site.url }}/images/start/google-sheet.png" alt="Google sheets"></a>
              </div>
            </article>
          </div>
        </div>
      </div>
    </div>
  </div>
</section>

<section class="section is-small">
  <div class="container">
    <h2 class="title is-1">Maintenance</h2>

    <div class="content is-medium">
      <ul>
        <li>⚠️ <strong>USB Connectors on WeMos D1 Mini vs WeMos battery shield</strong>
          <ul>
            <li>Do not plug in the USB cable on WeMos D1 Mini while the battery shield is on the PCB</li>
            <li><strong>Flashing firmware</strong>: Remove the battery shield from the PCB and use the USB cable on the WeMos D1 mini</li>
          </ul>
        </li>
        <li>Charge the LiPo by plugging in the USB cable into the battery shield</li>
      </ul>
    </div>
  </div>
</section>
