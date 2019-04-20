#include <ESP8266WiFi.h>
#include "Adafruit_Si7021.h"

#define EN 2 // GPIO02 on ESP-01 module, D4 on nodeMCU WeMos
#define USERBUTTON 12 // GPIO012 on ESP or D6 on WeMos

int dataPin = 13; // pin D7 `GPIO13` on NodeMCU boards
int clockPin = 14; // pin D5 `GPIO14` on NodeMCU boards
int latchPin = 15; // pin D8 `GPIO15` on NodeMCU boards

Adafruit_Si7021 sensor = Adafruit_Si7021();

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(2000);
  while(!Serial) { }

  int userButtonValue = digitalRead(USERBUTTON);

  Serial.println("\nI'm awake !!");

  if (userButtonValue == 0) {
    Serial.println("User long pressed button!");
  }

  initShiftRegister();
  initTempHumiditySensor();

  // Test 5 LEDs and shift register
  displayLED(0);
  delay(500);

  displayLED(1);
  delay(500);

  displayLED(3);
  delay(500);

  displayLED(7);
  delay(500);

  displayLED(15);
  delay(500);

  displayLED(31);
  delay(500);
}

void loop() {
  // Test Si7021 Temperature and humidity sensor
  displayHumidity();
  delay(1000);

  Serial.println("Going into deep sleep for 10s, unless button pressed...");

  // Disable LEDs and shift register
  digitalWrite(EN, LOW);
  displayLED(0);

  ESP.deepSleep(10e6);
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
    Serial.println("Did not find Si7021 sensor!");
    while (true)
      ;
  }
}

void displayLED(int lednumber) {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, lednumber);
  digitalWrite(latchPin, HIGH);
  Serial.println(lednumber);
}

void displayHumidity(void) {
  Serial.print("Temperature: ");
  Serial.print(sensor.readTemperature());
  Serial.print("\tHumidity:    ");
  Serial.print(sensor.readHumidity());

  int barHumidity = sensor.readHumidity()/20 + 1;
  String sBar = "\tGraph: " + String(barHumidity) + " bars";
  Serial.println(sBar);

  displayLED(pow(2, barHumidity) -1);
}
