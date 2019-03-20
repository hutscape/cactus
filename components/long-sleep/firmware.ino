// INFO: Sleep for more than 1 hour using EEPROM

// Hardware: nodeMCU to button for interrupt
// Short pin D0 to pin RST
// Note: Un-short the 2 pins above during uploading firmware

#include <EEPROM.h>

extern "C" {
  #include "user_interface.h"
}

const int sleepTime = 3600; // 3600 seconds = 1 hour

#define FINAL_SLEEP_INTERVAL 6 // 6 * sleepTime = 6 hours
#define CURRENT_SLEEP_INTERVAL_ADDR 30 // EEPROM address to store sleep interval
#define CURRENT_SLEEP_INTERVAL EEPROM.read(CURRENT_SLEEP_INTERVAL_ADDR)

int latchPin = 15; // pin D8 on NodeMCU boards
int clockPin = 14; // pin D5 on NodeMCU boards
int dataPin = 13; // pin D7 on NodeMCU boards

void setup() {
  EEPROM.begin(512);
  Serial.begin(115200);
  pinMode(2, OUTPUT);
  Serial.println("[INFO] Wake up!");

  if (CURRENT_SLEEP_INTERVAL == FINAL_SLEEP_INTERVAL) {
    blink(5);
    resetSleepInterval();
    doSomething();
    goToSleep();
  } else {
    blink(5);
    increaseSleepInterval();
    goToSleep();
  }
}

void blink(int times) {
  for (int i=0; i <= times; i++){
    digitalWrite(2, HIGH);
    delay(1000);

    digitalWrite(2, LOW);
    delay(1000);
  }
}
void loop() {}

void doSomething() {
  Serial.println("[INFO] Hey do something finally :)");
}

void goToSleep() {
  ESP.deepSleep(sleepTime * 1000000);
}

void resetSleepInterval() {
  EEPROM.write(CURRENT_SLEEP_INTERVAL_ADDR, 0);
  EEPROM.commit();
}

void increaseSleepInterval() {
  EEPROM.write(CURRENT_SLEEP_INTERVAL_ADDR, CURRENT_SLEEP_INTERVAL + 1);
  EEPROM.commit();
}
