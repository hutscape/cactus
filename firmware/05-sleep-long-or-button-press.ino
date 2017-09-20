// INFO: Wake up after every long sleep interval or button press

// Hardware: nodeMCU to button for interrupt
// Short pin D0 to pin RST
// Note: Un-short the 2 pins above during uploading firmware

#include <EEPROM.h>

extern "C" {
  #include "user_interface.h"
}

const int sleepTime = 10; // 10 seconds

#define FINAL_SLEEP_INTERVAL 6
#define CURRENT_SLEEP_INTERVAL_ADDR 30 // EEPROM address to store sleep interval
#define CURRENT_SLEEP_INTERVAL EEPROM.read(CURRENT_SLEEP_INTERVAL_ADDR)
#define BUTTON_PRESS 12 // GPIO12 or D6

int latchPin = 15; // pin D8 on NodeMCU boards
int clockPin = 14; // pin D5 on NodeMCU boards
int dataPin = 13; // pin D7 on NodeMCU boards

void setup() {
  EEPROM.begin(512);
  Serial.begin(115200);
  pinMode(2, OUTPUT);
  Serial.println("[INFO] Wake up!");

  readPin();

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

void readPin() {
  Serial.print("[INFO] Read pin GPIO12 / D6: ");
  Serial.println(digitalRead(BUTTON_PRESS));

  Serial.print("[INFO] Reset reason: ");
  Serial.println(getResetReason());
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
  Serial.println("[INFO] Going to sleep for 10 seconds...");
  ESP.deepSleep(sleepTime * 1000000);
}

void resetSleepInterval() {
  Serial.println("[INFO] ");
  EEPROM.write(CURRENT_SLEEP_INTERVAL_ADDR, 0);
  EEPROM.commit();
}

void increaseSleepInterval() {
  EEPROM.write(CURRENT_SLEEP_INTERVAL_ADDR, CURRENT_SLEEP_INTERVAL + 1);
  EEPROM.commit();
}

int getResetReason() {
  rst_info* ri = system_get_rst_info();
  if (ri == NULL) {
    return -1;
  }

  return ri->reason;
}
