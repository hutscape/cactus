---
layout: default
title: Getting Started
permalink: /
sequence: 1
---

<section class="section is-small">
  <div class="container">
    <h1 class="title is-1">Getting Started</h1>

    <div class="columns">
      <div class="column is-one-quarter">
        <p class="subtitle is-4">1. Setup an <a href="https://ifttt.com/services/maker_webhooks">IFTTT webhook</a> to receive a POST request with data and add a row to a Google Spreadsheet</p>
      </div>
      <div class="column is-one-third">
        <img src="firmware/ifttt.png" alt="IFTTT">
      </div>
    </div>

    <div class="columns">
      <div class="column is-one-quarter">
        <p class="subtitle is-4">2. Connect to the access point</p>
      </div>
      <div class="column is-one-third">
        <img src="firmware/access_point.png" alt="Access point">
      </div>
    </div>

    <div class="columns">
      <div class="column is-one-quarter">
        <p class="subtitle is-4">3. Go to the web page <code>http://cactus.local</code> to fill in the WiFi credentials and <a href="https://ifttt.com/services/maker_webhooks/settings">IFTTT webhook key</a></p>
      </div>
      <div class="column is-one-third">
        <img src="firmware/webpage.png" alt="Webpage form">
        <img src="firmware/webpage-received.png" alt="Webpage form recived">
      </div>
    </div>

    <div class="columns">
      <div class="column is-one-quarter">
        <p class="subtitle is-4">4. Wait for the <a href="https://docs.google.com/spreadsheets/d/1qedLXiCeU6vCwEvv3JqwrVWjrriB8L3DA9Xp-g01Jk0/edit?usp=sharing">Google Sheet</a> to update with a new row</p>
      </div>
      <div class="column is-one-third">
        <img src="firmware/google-sheet.png" alt="Google sheets">
      </div>
    </div>
  </div>
</section>

<section class="section is-small">
  <div class="container">
    <h1 class="title is-1">Maintenance</h1>

    - ⚠️ **USB Connectors on WeMos D1 Mini vs WeMos battery shield**
        - Do not plug in the USB cable on WeMos D1 Mini while the battery shield is on the PCB
        - **Flashing firmware**: Remove the battery shield from the PCB and use the USB cable on the WeMos D1 mini
    - Charge the LiPo by plugging in the USB cable into the battery shield

  </div>
</section>
