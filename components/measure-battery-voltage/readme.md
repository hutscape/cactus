# Measure Battery Level

> Measure the LiPo battery voltage

## Hardware

1. Connect `100k` resistor from `A0` to JST connector's positive terminal

![](../hardware/images/battery-shield.jpg)

## Firmware

Flash the [firmware](measure-battery-voltage.ino)

## Instructions

1. Power via LiPo through the JST connector on the WeMos battery shield and not via the USB power on the WeMos
1. Connect to access point `Cactus XXXX` with password `hutscape`
1. Get the current battery voltage by accessing `192.168.4.1`

![](webpage.png)

## Reference

- [Monitoring LiPo battery voltage with Wemos D1 mini battery shield and Thingspeak](https://arduinodiy.wordpress.com/2016/12/25/monitoring-lipo-battery-voltage-with-wemos-d1-minibattery-shield-and-thingspeak/)