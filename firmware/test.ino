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

  Serial.println("\nTest 1: It expects to wake up periodically");

  if (userButtonValue == 0) {
    Serial.println("Test 8: It expects to wake up on user long press");
  }

  initShiftRegister();
  initTempHumiditySensor();

  // Test 5 LEDs and shift register
  displayLED(0);
  delay(500);

  Serial.println("Test 2: It expects to make LED 1 ON");
  displayLED(1);
  delay(500);

  Serial.println("Test 3: It expects to make LED 1, LED 2 ON");
  displayLED(3);
  delay(500);

  Serial.println("Test 4: It expects to make LED 1, LED 2, LED 3 ON");
  displayLED(7);
  delay(500);

  Serial.println("Test 5: It expects to make LED 1, LED 2, LED 3, LED 4 ON");
  displayLED(15);
  delay(500);

  Serial.println("Test 6: It expects to make LED 1, LED 2, LED 3, LED 4, LED 5 ON");
  displayLED(31);
  delay(500);
}

void loop() {
  Serial.println("Test 7: It expects to read the current temperature and humidity");
  displayTempHumidity();

  disableLEDs();

  Serial.println("Going into deep sleep for 10s, unless button pressed...");
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
}

void displayTempHumidity(void) {
  Serial.print("\tTemperature: ");
  Serial.print(sensor.readTemperature());
  Serial.print(" °C\tHumidity: ");
  Serial.print(sensor.readHumidity());
  Serial.print(" RH%");

  int barHumidity = sensor.readHumidity()/20 + 1;
  String sBar = "\tGraph: " + String(barHumidity) + " LEDs";
  Serial.println(sBar);

  displayLED(pow(2, barHumidity) -1);
}

void disableLEDs(void) {
  digitalWrite(EN, LOW);
  displayLED(0);
}
