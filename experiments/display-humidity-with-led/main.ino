// INFO: Display humidity in a bar graph LED

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
