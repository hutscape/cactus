---
layout: code
title: Web configuration
description: Test that all features work
difficulty: medium
features:
  - temperature
  - humidity
  - wifi
code: html
---

A web portal to configure the device with the following:

- WiFI SSID
- WiFi password
- IFTTT key
- IFTTT event name

This web config page is displayed when the device is in the configuration mode to setup WiFi and IFTTT credentials. It uses <a href="https://bulma.io">Bulma CSS</a> with <a href="https://uncss-online.com/">UnCSS</a> to extract only the used CSS styles so that no CDN access is required in the Access Point mode.
