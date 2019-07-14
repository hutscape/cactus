---
layout: default
title: Getting Started
permalink: /
sequence: 1
---

<section class="section is-small">
  <div class="container">
    <h2 class="title is-1">Getting Started</h2>

    <div class="tile is-ancestor">
      <div class="tile is-vertical is-8">
        <div class="tile">
          <div class="tile is-parent is-vertical">
            <article class="tile is-child notification">
              <p class="title">Step 1</p>
              <p class="subtitle">Setup an <a href="https://ifttt.com/services/maker_webhooks">IFTTT webhook</a> to receive a POST request with data and add a row to a Google Spreadsheet.</p>
              <img src="firmware/ifttt.png" alt="IFTTT">
            </article>
          </div>
          <div class="tile is-parent">
            <article class="tile is-child notification">
              <p class="title">Step 2</p>
              <p class="subtitle">Connect to the WiFi access point <code>Cactus {UNIQUE_MAC_ADDRESS}</code>.</p>
              <img src="firmware/access_point.png" alt="Access point">
            </article>
          </div>
        </div>
        <div class="tile is-parent">
          <article class="tile is-child notification">
            <p class="title">Step 4</p>
            <p class="subtitle">Wait for the <a href="https://docs.google.com/spreadsheets/d/1qedLXiCeU6vCwEvv3JqwrVWjrriB8L3DA9Xp-g01Jk0/edit?usp=sharing">Google Sheet</a> to update with a new row.</p>
            <img src="firmware/google-sheet.png" alt="Google sheets">
          </article>
        </div>
      </div>
      <div class="tile is-parent">
        <article class="tile is-child notification">
          <div class="content">
            <p class="title">Step 3</p>
            <p class="subtitle">Go to the web page <code>http://cactus.local</code> to fill in the WiFi credentials and <a href="https://ifttt.com/services/maker_webhooks/settings">IFTTT webhook key</a>.</p>
            <img src="firmware/webpage.png" alt="Webpage form">
            <img src="firmware/webpage-received.png" alt="Webpage form recived">
          </div>
        </article>
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
