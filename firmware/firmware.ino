#include <EEPROM.h>
#include <ESP8266WiFi.h>

#define USERBUTTON 12 // GPIO012 on ESP or D6 on WeMos
#define SLEEP_INTERVAL_DURATION  10e6 // 10 seconds
#define SLEEP_DURATION_ENGLISH "10 seconds"
#define CURRENT_SLEEP_COUNT EEPROM.read(CURRENT_SLEEP_INTERVAL_ADDR)
#define MAX_SLEEP_COUNT 3 // 3*10 seconds = 30 seconds
#define CURRENT_SLEEP_INTERVAL_ADDR 30 // EEPROM address to store sleep interval
#define DEBUG true

int userButtonValue = 1;

void setup() {
  Serial.begin(115200);
  EEPROM.begin(512);
  userButtonValue = digitalRead(USERBUTTON);

  debugPrintln("[INFO] Wakeup!");

  if (!isCurrentSleepCountMax() && !hasUserPressedButton(userButtonValue)) {
    increaseSleepCount();
    goToSleep();
    return;
  }

  resetSleepCount();
  doTask();

  debugPrint("[INFO] Going into deep sleep for ");
  debugPrintln(SLEEP_DURATION_ENGLISH);
  goToSleep();
}

void loop() {
}

// Print functions
void debugPrintln(String s) {
  if (DEBUG) {
    Serial.println(s);
  }
}

void debugPrint(String s) {
  if (DEBUG) {
    Serial.print(s);
  }
}

void doTask() {
  debugPrintln("[INFO] Do task");
}

// EEPROM functions
bool isCurrentSleepCountMax() {
  return CURRENT_SLEEP_COUNT >= MAX_SLEEP_COUNT;
}

void increaseSleepCount() {
  EEPROM.write(CURRENT_SLEEP_INTERVAL_ADDR, CURRENT_SLEEP_COUNT + 1);
  EEPROM.commit();
}

void resetSleepCount() {
  EEPROM.write(CURRENT_SLEEP_INTERVAL_ADDR, 0);
  EEPROM.commit();
}

// Sensors
bool hasUserPressedButton(int userButtonValue) {
  return userButtonValue == 0;
}

void goToSleep() {
  WiFi.disconnect( true );
  delay(1);
  ESP.deepSleep(SLEEP_INTERVAL_DURATION, WAKE_RF_DISABLED);
}
