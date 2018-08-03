#define RTCMEMORYSTART 65
#define RTCMEMORYSIZE 8
#define MAXHOUR 2 // number of times to deep sleep
#define TIMEINTERVAL 10000000 // 10 seconds

// Edit "secret" ssid and password below
const char* ssid = "secret";
const char* password = "secret";

#include <ESP8266WiFi.h>

extern "C" {
#include "user_interface.h"
}

typedef struct {
  int count;
  int doAction;
} rtcStore;

rtcStore rtcMem;

void setup() {
  Serial.begin(115200);
  Serial.println("");

  Serial.println("Waking up...");

  Serial.print("Reading ");
  readFromRTCMemory();

  if (rtcMem.count == 0) {
    if (rtcMem.doAction == 1) {
      Serial.println("Connect to WiFi!");
      connectToWifi();
    } else if (rtcMem.doAction == 0) {
      Serial.println("Prepare to doAction something!");
      prepareToDoSomething();
    }
  } else {
    Serial.println("Just go back to sleep again");
  }

  writeToRTCMemory();

  Serial.print("Sleeping for 10 seconds. ");
  ESP.deepSleep(TIMEINTERVAL, WAKE_RF_DISABLED);
}

void loop() {}

void prepareToDoSomething() {
  rtcMem.doAction = 1;
  system_rtc_mem_write(RTCMEMORYSTART, &rtcMem, RTCMEMORYSIZE);
  yield();
  ESP.deepSleep(1, WAKE_RF_DEFAULT);
}

void connectToWifi() {
  Serial.print("Connecting to SSID ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  int count = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    count++;
    Serial.print(".");

    if (count > 20) {
      break;
    }
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    Serial.println("Time to read the sensor and send to cloud!");
  } else {
    Serial.println("");
    Serial.println("WiFi could not be connected !!!!");
  }

}

void readFromRTCMemory() {
  system_rtc_mem_read(RTCMEMORYSTART, &rtcMem, sizeof(rtcMem));

  Serial.print("size of rtcMem: ");
  Serial.print(sizeof(rtcMem));
  Serial.print(", count = ");
  Serial.print(rtcMem.count);
  Serial.print(", doAction? = ");
  Serial.println(rtcMem.doAction);
  yield();
}

void writeToRTCMemory() {
  if (rtcMem.count <= MAXHOUR && rtcMem.count >= 0) {
    rtcMem.count++;
    rtcMem.doAction = 0;
  } else {
    rtcMem.count = 0;
    rtcMem.doAction = 0;
  }

  system_rtc_mem_write(RTCMEMORYSTART, &rtcMem, RTCMEMORYSIZE);
  yield();

  Serial.print("Writing ");
  Serial.print("count = ");
  Serial.print(rtcMem.count);
  Serial.print(", doAction = ");
  Serial.println(rtcMem.doAction);
}
