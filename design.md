---
layout: design
title: Design
permalink: /design
sequence: 5
state_machine: true

# Mechanical
items:
  - name: Name card holder box
    url: https://www.adafruit.com/product/3406
    height: 90
    width: 55
    depth: 25
    dimension_unit: mm
    comment: enclosure

  - name: PCB
    height: 76
    width: 38
    depth: 2
    dimension_unit: mm

  - name: WeMos D1 Mini V3.0.0
    url: https://wiki.wemos.cc/products:d1:d1_mini
    height: 34.2
    width: 25.6
    depth: 2
    dimension_unit: mm
    weight: 3
    weight_unit: g
    comment: pcb fit

  - name: WeMos Battery shield
    url: https://wiki.wemos.cc/products:d1_mini_shields:battery_shield
    height: 34.2
    width: 25.6
    depth: 2
    dimension_unit: mm
    comment: pcb fit

  - name: Adafruit Si7021 Breakout Board
    url: https://www.adafruit.com/product/3251
    height: 17.8
    width: 15.3
    depth: 3
    dimension_unit: mm
    weight: 1
    weight_unit: g
    comment: pcb fit

  - name: <code>500mAh</code> LiPo
    url: https://www.adafruit.com/product/1578
    height: 36
    width: 29
    depth: 4.75
    dimension_unit: mm
    weight: 10.5
    weight_unit: g
    comment: pcb fit

  - name: <code>500mAh</code> LiPo
    url: https://www.aliexpress.com/item/3-7V-500mAh-Lipo-Battery-For-Syma-X5C-X5SW-M68-Cheerson-CX-30-H5C-Quadrocopter-3/32918919539.html
    height: 43
    width: 25
    depth: 8
    dimension_unit: mm
    comment: pcb fit

  - name: <code>2000mAh</code> LiPo
    url: https://www.adafruit.com/product/2011
    height: 60
    width: 36
    depth: 7
    dimension_unit: mm
    weight: 34
    weight_unit: g
    comment: pcb fit

  - name: <code>2000mAh</code> LiPo
    url: https://www.aliexpress.com/item/3-7V-2000-mAh-Polymer-Lithium-Battery-LiPo-For-GPS-Tablet-PC-407080/2055208577.html
    height: 80
    width: 70
    depth: 4
    dimension_unit: mm

  - name: <code>2500mAh</code> LiPo
    url: https://www.adafruit.com/product/328
    height: 65
    width: 51
    depth: 8
    dimension_unit: mm
    weight: 52
    weight_unit: g

# Power

power_tree: true
power_source: <code>2000mAh</code> LiPo battery
battery_life: 1 month
charging_duration: 12 hours
charging_instruction: Remove the WeMos Battery shield from the board. Plug in the USB cable to the WeMos battery shield to charge. <code>Red</code> LED will be on while it is charging.<code>Green</code> LED will be on when charging is complete.
---


<section class="section is-small">
  <div class="container">
    <h2 class="title is-1">Power consumption of main components</h2>
    <table class="table is-fullwidth">
      <thead>
        <tr>
          <th>Chip #</th>
          <th>Chip</th>
          <th>Operating Voltage</th>
          <th>Active mode</th>
          <th>Modem-sleep mode</th>
          <th>Deep-sleep mode</th>
          <th>Total</th>
        </tr>
      </thead>
      <tbody>
        <tr>
          <td>ESP8266</td>
          <td>WiFi based MCU</td>
          <td><code>3.3V</code></td>
          <td><code>170mA</code></td>
          <td><code>15mA</code></td>
          <td><code>10uA</code></td>
          <td></td>
        </tr>
        <tr>
          <td>Si7021</td>
          <td>Temperature / Humidity sensor</td>
          <td><code>1.9V</code> - <code>3.6V</code></td>
          <td><code>150uA</code></td>
          <td></td>
          <td><code>60nA</code></td>
          <td></td>
        </tr>
        <tr>
          <td>SN4HC595</td>
          <td>Shift register</td>
          <td><code>2V</code> - <code>6V</code></td>
          <td><code>60uA</code></td>
          <td></td>
          <td><code>1uA</code></td>
          <td></td>
        </tr>
        <tr class="is-selected">
          <td>Total consumption</td>
          <td></td>
          <td></td>
          <td><code>170.23mA</code></td>
          <td><code>15mA</code></td>
          <td><code>11.06uA</code></td>
          <td></td>
        </tr>
        <tr class="is-selected">
          <td>Total duration</td>
          <td></td>
          <td></td>
          <td>30s.</td>
          <td>10s x 12 = 120s.</td>
          <td>4h.</td>
          <td>4h.</td>
        </tr>
        <tr class="is-selected">
          <td>Total charge</td>
          <td></td>
          <td></td>
          <td>30/14400 * 170.21m <br>= 0.354 mAs</td>
          <td>120/14400 *15m <br>= 0.125mAs</td>
          <td>14250/14400 * 11.06u <br>= 0.011mAs</td>
          <td>0.589mAs</td>
        </tr>
      </tbody>
    </table>
  </div>
</section>

<section class="section is-small">
  <div class="container">
    <h2 class="title is-1">Power calculation</h2>
    <div class="content is-medium">
      <p>3 power modes:</p>
      <ol>
        <li>Wakes up in <strong>Active mode</strong> for 30 seconds every 4 hours to read the sensor value and ping to cloud</li>
        <li>Wakes up in <strong>Mode-sleep mode</strong> for <strong>10 seconds</strong> every <strong>20 minutes</strong> to check whether the counter has reached the threshold</li>
        <li><strong>Deep-sleep mode</strong> for the rest of the time, unless user button pressed</li>
      </ol>
      <p><code>1200mAh</code> battery will last for <code>(1200/24/30)</code> = <strong>2.89 months</strong></p>
    </div>
  </div>
</section>

<section class="section is-small">
  <div class="container">
    <h2 class="title is-1">Measuring power</h2>
    <table class="table is-fullwidth">
      <thead>
        <tr>
          <td>Mode</td>
          <td>Pins</td>
          <td>Voltage</td>
        </tr>
      </thead>
      <tbody>
        <tr>
          <td>Deep sleep</td>
          <td><code>5V</code> - <code>GND</code> on WeMos D1 mini</td>
          <td><code>4.94V</code></td>
        </tr>
        <tr>
          <td>Deep sleep</td>
          <td><code>Vin</code> - <code>GND</code> on Si7021 breakout board</td>
          <td><code>5V</code></td>
        </tr>
        <tr>
          <td>Deep sleep</td>
          <td><code>Vcc</code> - <code>GND</code> on 74HC595 chip</td>
          <td><code>5V</code></td>
        </tr>
        <tr>
          <td>Deep sleep</td>
          <td><code>EN</code> - <code>GND</code> on 74HC595 chip</td>
          <td></td>
        </tr>
      </tbody>
    </table>
  </div>
</section>

<section class="section is-small">
  <div class="container">
    <h2 class="title is-1">Actual vs. calculated power</h2>
    <table class="table is-fullwidth">
      <thead>
        <tr>
          <td>Periodic wakeup</td>
          <td>Calculated</td>
          <td>Actual</td>
          <td>Error %</td>
        </tr>
      </thead>
      <tbody>
        <tr>
          <td>6 hours</td>
          <td>2.89 months</td>
          <td>30 days</td>
          <td>~300% ⁉️</td>
        </tr>
      </tbody>
    </table>
  </div>
</section>
