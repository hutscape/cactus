#include <EEPROM.h>
#include <ESP8266WiFi.h>

#define DEBUG true

#define USERBUTTON 12 // GPIO012 on ESP or D6 on WeMos
#define SLEEP_INTERVAL_DURATION  10e6 // 10 seconds
#define SLEEP_DURATION_ENGLISH String("10 seconds")
#define CURRENT_SLEEP_COUNT EEPROM.read(CURRENT_SLEEP_INTERVAL_ADDR)
#define MAX_SLEEP_COUNT 3 // 3*10 seconds = 30 seconds
#define CURRENT_SLEEP_INTERVAL_ADDR 30 // EEPROM address to store sleep interval
#define MAX_WIFI_RECONNECT_INTERVAL 20 // 20 seconds

char ssid [50] = "secret";
char password [50] = "secret";
String AP_NamePrefix = "Cactus ";
const char WiFiAPPSK[] = "hutscape";
int userButtonValue = 1;

void setup() {
  EEPROM.begin(512);
  Serial.begin(115200);

  disableWiFi();
  debugPrintln("");
  userButtonValue = digitalRead(USERBUTTON);

  debugPrintln("[INFO] Wakeup sleep count " + String(CURRENT_SLEEP_COUNT) + "/" + String(MAX_SLEEP_COUNT));

  if (!isCurrentSleepCountMax() && !hasUserPressedButton(userButtonValue)) {
    increaseSleepCount();

    debugPrintln("[INFO] Going into deep sleep for " + SLEEP_DURATION_ENGLISH);
    goToSleep();
    return;
  }

  resetSleepCount();

  if (hasUserPressedButton(userButtonValue)) {
    debugPrintln("[INFO] Wakeup on user button press!");
  }

  enableWiFi();
  bool isConnectedToWiFi = connectToWiFi();
  if (isConnectedToWiFi) {
    debugPrintln("[INFO] Connected succesfully to WiFi SSID " + WiFi.SSID());
    doTask();
  } else {
    debugPrintln("[ERROR] Connection to WiFi failed.");
    debugPrintln("[INFO] Configuring access point");
    initAccessPoint();
    debugPrintln("[INFO] Started access point at IP " + WiFi.softAPIP().toString());
  }

  // debugPrintln("[INFO] Going into deep sleep for " + SLEEP_DURATION_ENGLISH);
  // goToSleep();
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

// Sensor functions
bool hasUserPressedButton(int userButtonValue) {
  return userButtonValue == 0;
}

// Sleep and Wakup functions
void goToSleep() {
  WiFi.disconnect( true );
  delay(1);

  ESP.deepSleep(SLEEP_INTERVAL_DURATION, WAKE_RF_DISABLED);
}

// WiFi functions
void enableWiFi() {
  WiFi.forceSleepWake(); // wakeup WiFi modem
  delay(1);
}

void disableWiFi() {
  WiFi.mode(WIFI_OFF);
  WiFi.forceSleepBegin();
  delay(1);
}

bool connectToWiFi() {
  WiFi.persistent(true); // last used Wi-Fi info in flash
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  int count = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);

    if (++count % 10 == 0) {
      debugPrintln(".");
    } else {
      debugPrint(".");
    }

    if (count > MAX_WIFI_RECONNECT_INTERVAL) {
      return false;
    }
  }

  if (count % 10 != 0){
    debugPrintln("");
  }

  WiFi.setAutoConnect(true);
  WiFi.setAutoReconnect(true);
  return true;
}

void initAccessPoint() {
  // TODO: Blink LED to indicate that user has to put in the credentials in AP mode
  WiFi.mode(WIFI_AP);
  WiFi.softAP(createAPName().c_str(), WiFiAPPSK);

  // startMDNS();
  // startServer();
}

String createAPName() {
  uint8_t mac[WL_MAC_ADDR_LENGTH];
  WiFi.softAPmacAddress(mac);
  String macID = String(mac[WL_MAC_ADDR_LENGTH - 2], HEX) +
                 String(mac[WL_MAC_ADDR_LENGTH - 1], HEX);
  macID.toUpperCase();
  return AP_NamePrefix + macID;
}
