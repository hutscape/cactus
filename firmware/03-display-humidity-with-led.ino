// INFO: Display humidity in a bar graph LED

// Hardware: nodeMCU with shift register 74hc595 and 5 LEDs
// - DS pin 14 to Digital pin D7 on nodeMCU (data pin)
// - SH_CP pin 11 to Digital pin D5 on nodeMCU (clock pin)
// - ST_CP pin 12 to Digital pin D8 on nodeMCU (latch pin)
// - GND pin 8 to GND
// - Vcc pin 16 to 5V
// - OE pin 13 to GND
// - MR pin 10 to 5V
// - pin 1 to LED 1 and then 1kΩ resistor to GND
// - pin 2 to LED 2 and then 1kΩ resistor to GND
// - pin 3 to LED 3 and then 1kΩ resistor to GND
// - pin 4 to LED 4 and then 1kΩ resistor to GND
// - pin 5 to LED 5 and then 1kΩ resistor to GND

// Hardware: nodeMCU with Si7021 Adafruit breakout board
// - `VIN` on si7021 and `3V3` on nodeMCU
// - `GND` on si7021 and `G` on nodeMCU
// - `SDA` on si7021 and `D2` on nodeMCU
// - `SCL` on si7021 and `D1` on nodeMCU

#include <SI7021.h>

#define SDA 4 // GPIO4 on ESP-01 module, D2 on nodeMCU WeMos
#define SCL 5 // GPIO5 on ESP-01 module, D1 on nodeMCU WeMos

int latchPin = 15; // pin D8 on NodeMCU boards
int clockPin = 14; // pin D5 on NodeMCU boards
int dataPin = 13; // pin D7 on NodeMCU boards

SI7021 sensor;

void setup() {
  sensor.begin(SDA,SCL);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  int temperature = sensor.getCelsiusHundredths();
  int humidity = sensor.getHumidityPercent();
  int barHumidity = humidity/20 + 1;
  String sTemperature = "Temperature: " + String(temperature/100)+ "°C";
  String sHumidity = "Humidity: " + String(humidity) + " RH%";
  String sBar = "Graph: " + String(barHumidity) + " bars";

  Serial.println(sTemperature);
  Serial.println(sHumidity);
  Serial.println(sBar);
  Serial.println("");
  display(barHumidity);

  delay(2000);
}

int display(int barValue) {
  int position = 0;

  if (barValue == 1) {
    position = 2;
  } else if (barValue == 2) {
    position = 6;
  } else if (barValue == 3) {
    position = 14;
  } else if (barValue == 4) {
    position = 30;
  } else {
    position = 62;
  }

  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, position);
  digitalWrite(latchPin, HIGH);
}
