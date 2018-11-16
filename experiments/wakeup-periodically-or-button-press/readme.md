# Wake up periodically or on button press

Display and send sensor data to cloud periodically on wake up after deep sleep or by pressing the button on-board

## Hardware

![Wiring](schematic.jpg)

## Firmware [[link](main.ino)]

Features:

- Wakeup
  - periodically without any WiFi to save battery
  - upon user button press
- Increment the interval count on the RTC memory
- Connect to WiFi and do something only if the interval count of the wakeup is correct or the user has pressed button

![](console.png)

## References

- [Synchro Clock config pin schematic](https://raw.githubusercontent.com/liebman/AnalogClock/master/images/SynchroClock.png)
- [Circuit simulation](https://www.falstad.com/circuit/circuitjs.html?cct=$+1+0.000005+100.89512123094175+50+5+43%0AR+176+128+176+80+0+0+40+3.3+0+0+0.5%0Ag+176+320+176+368+0%0As+96+320+176+320+0+1+true%0Ar+176+272+304+272+0+1000%0Ar+96+128+96+224+0+10000%0Ac+96+224+224+224+0+0.00001+-2.4593660441496468e-11%0Ar+224+128+224+224+0+10000%0Aw+96+128+176+128+0%0Aw+224+128+176+128+0%0Aw+224+224+304+224+0%0Ar+304+224+304+128+0+1000%0Aw+304+128+432+128+2%0Aw+304+224+384+224+2%0Aw+176+272+96+272+0%0Aw+96+224+96+272+0%0Aw+96+272+96+320+0%0Aw+304+272+384+272+2%0As+432+128+528+128+0+1+true%0Ag+528+128+528+160+0%0Ar+432+128+432+80+0+1000%0AR+432+80+432+32+0+0+40+3.3+0+0+0.5%0Ab+400+16+570+179+0%0Ax+394+230+442+233+4+24+RST%0Ax+472+54+558+57+4+24+GPIO16%0Ax+396+282+482+285+4+24+GPIO12%0A)
