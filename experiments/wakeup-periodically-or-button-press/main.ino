#include <ESP8266WiFi.h>
#define USERBUTTON 12 // GPIO012 on ESP or D6 on WeMos

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(2000);
  int userButtonValue = digitalRead(USERBUTTON);

  while(!Serial) { }

  Serial.println("\nI'm awake !!");

  if (userButtonValue == 0) {
    Serial.println("User long pressed button!");
  }

  Serial.println("Read the sensor and send to cloud.");
  Serial.println("Going into deep sleep for 20s, unless button pressed...");
  ESP.deepSleep(20e6);
}

void loop() {
}
