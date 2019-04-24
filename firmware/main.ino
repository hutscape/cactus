#include "Adafruit_Si7021.h"

#define EN 2 // GPIO02 on ESP-01 module, D4 on nodeMCU WeMos

int dataPin = 13; // pin D7 `GPIO13` on NodeMCU boards
int clockPin = 14; // pin D5 `GPIO14` on NodeMCU boards
int latchPin = 15; // pin D8 `GPIO15` on NodeMCU boards

Adafruit_Si7021 sensor = Adafruit_Si7021();

void setup() {
  Serial.begin(115200);
  while(!Serial) { }

  pinMode(A0, INPUT);

  initShiftRegister();
  initTempHumiditySensor();
}

void loop() {
  displayTempHumidity();
  displayBattery();
  delay(2000);
}

void initShiftRegister() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  pinMode(EN, OUTPUT);
  digitalWrite(EN, LOW);
}

void initTempHumiditySensor() {
  if (!sensor.begin()) {
    Serial.println("[ERROR] Did not find Si7021 sensor!");
    while (true)
      ;
  }
}

void displayLED(int lednumber) {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, lednumber);
  digitalWrite(latchPin, HIGH);
}

void displayTempHumidity(void) {
  Serial.print("[INFO] Temperature: ");
  Serial.print(sensor.readTemperature());
  Serial.print(" °C\tHumidity: ");
  Serial.print(sensor.readHumidity());
  Serial.print(" RH%");

  int barHumidity = sensor.readHumidity()/20 + 1;
  String sBar = "\tGraph: " + String(barHumidity) + " LEDs";
  Serial.println(sBar);

  displayLED(pow(2, barHumidity) -1);
}

void displayBattery(void) {
  Serial.print("[INFO] Battery: ");

  unsigned int raw = analogRead(A0);
  float volt = raw / 1023.0;
  volt = volt * 4.2;

  String v = String(volt);
  Serial.println(raw);
}
