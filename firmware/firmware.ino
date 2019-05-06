#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Ticker.h>
#include <math.h>
#include "Adafruit_Si7021.h"

#define DEBUG true

#define EN 2 // GPIO02 on ESP-01 module, D4 on nodeMCU WeMos, or on-board LED
#define LED 2
#define BATTERY_VOLT A0
#define USERBUTTON 12 // GPIO012 on ESP or D6 on WeMos
#define SLEEP_INTERVAL_DURATION  10e6 // 10 seconds
#define SLEEP_DURATION_ENGLISH String("10 seconds")
#define CURRENT_SLEEP_COUNT EEPROM.read(CURRENT_SLEEP_INTERVAL_ADDR)
#define MAX_SLEEP_COUNT 3 // 3*10 seconds = 30 seconds
#define CURRENT_SLEEP_INTERVAL_ADDR 30 // EEPROM address to store sleep interval
#define MAX_WIFI_RECONNECT_INTERVAL 20 // WiFi will try to connect for 20 seconds
#define MAX_AP_ON_MINUTES 1 // The AP mode will be on for 1 minute

// WiFi
char ssid [50] = "secret";
char password [50] = "secret";
String AP_NamePrefix = "Cactus ";
const char WiFiAPPSK[] = "hutscape";
const char* DomainName = "cactus"; // set domain name domain.local

// LEDs and shift register
int dataPin = 13; // pin D7 `GPIO13` on NodeMCU boards
int clockPin = 14; // pin D5 `GPIO14` on NodeMCU boards
int latchPin = 15; // pin D8 `GPIO15` on NodeMCU boards

struct SensorValues {
  float temperature;
  float humidity;
};

int userButtonValue = 1;
bool isAPWebServerRunning = false;
bool willEraseWiFiCredentials = false; // change to true if WiFi credentials need to be erased for reconnecting to a new SSID
int apLoopCount = 0;
Ticker ticker;
SensorValues sensorValues;

ESP8266WebServer server(80);
Adafruit_Si7021 sensor = Adafruit_Si7021();

void setup() {
  EEPROM.begin(512);
  Serial.begin(115200);

  disableWiFi();
  debugPrintln("");
  userButtonValue = digitalRead(USERBUTTON);

  debugPrintln("[INFO] Wakeup sleep count " + String(CURRENT_SLEEP_COUNT) + "/" + String(MAX_SLEEP_COUNT));

  if (willEraseWiFiCredentials) {
    eraseWiFiCredentials();
    debugPrintln("[INFO] Erasing WiFi credentials");
    debugPrintln("[INFO] Read empty WiFi SSID: " + WiFi.SSID());
  }

  if (!isCurrentSleepCountMax() && !hasUserPressedButton(userButtonValue)) {
    increaseSleepCount();
    debugPrintln("[INFO] Going into deep sleep for " + SLEEP_DURATION_ENGLISH);
    goToSleep();
    return;
  }

  initReadingBatteryVoltage();
  initTempHumiditySensor();
  resetSleepCount();
  sensorValues = readTempHumidity();

  if (hasUserPressedButton(userButtonValue)) {
    debugPrintln("[INFO] Wakeup on user button press!");
    initShiftRegister();
    displayHumidity(sensorValues.humidity);
  }

  enableWiFi();
  bool isConnectedToWiFi = connectToWiFi(true);
  if (isConnectedToWiFi) {
    debugPrintln("[INFO] Connected succesfully to WiFi SSID " + WiFi.SSID());
    debugPrintln("[INFO] WiFi connected! IP address: " + WiFi.localIP().toString());
  } else {
    debugPrintln("[ERROR] Connection to WiFi failed");
    debugPrintln("[INFO] Configuring access point");
    initAccessPoint();
    debugPrintln("[INFO] Started access point at IP " + WiFi.softAPIP().toString());

    bool hasMDNSStarted = MDNS.begin(DomainName, WiFi.softAPIP());
    if (!hasMDNSStarted) {
      debugPrintln("[ERROR] mDNS has failed to start");
    }

    startServer();
    debugPrintln("[INFO] WiFi is not configured!");
    debugPrintln("[INFO] Connect to SSID 'Cactus NNNN'");
    debugPrintln("[INFO] Go to http://cactus.local");

    // Start blinking LED to indicate AP mode
    pinMode(LED_BUILTIN, OUTPUT);
    ticker.attach(1, blink);
  }
}

void loop() {
  if (isAPWebServerRunning) {
    MDNS.update();
    server.handleClient();

    if (++apLoopCount > MAX_AP_ON_MINUTES*600) {
      debugPrintln("[INFO] Going into deep sleep for " + SLEEP_DURATION_ENGLISH);
      goToSleep();
    }
    delay(100);
  } else {
    ticker.detach();

    doTask();
    debugPrintln("[INFO] Going into deep sleep after task for " + SLEEP_DURATION_ENGLISH);
    goToSleep();
  }
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

void blink() {
  int state = digitalRead(LED_BUILTIN);
  digitalWrite(LED_BUILTIN, !state);
}

void ledOFF() {
  digitalWrite(LED_BUILTIN, HIGH);
}

void initShiftRegister() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  pinMode(EN, OUTPUT);
  digitalWrite(EN, LOW);
}

void initReadingBatteryVoltage() {
  pinMode(BATTERY_VOLT, INPUT);
}

void initTempHumiditySensor() {
  if (!sensor.begin()) {
    Serial.println("[ERROR] Did not find Si7021 sensor!");
    while (true)
      ;
  }
}

SensorValues readTempHumidity(void) {
  SensorValues sensorValues = { 0.0, 0.0 };

  // NOTE: Get 10 sensor values and smoothen it
  for (int count = 0; count < 10; count++) {
    sensorValues.temperature += sensor.readTemperature();
    sensorValues.humidity += sensor.readHumidity();
  }

  sensorValues.temperature /= 10;
  sensorValues.humidity /= 10;

  Serial.print("[INFO] Temperature: ");
  Serial.print(sensorValues.temperature);
  Serial.print(" C, Humidity: ");
  Serial.print(sensorValues.humidity);
  Serial.println(" RH%");

  return sensorValues;
}

void displayHumidity(float humidity) {
  int barHumidity = humidity/20 + 1;
  String sBar = "[INFO] Display Humidity in LED: " + String(barHumidity) + " LEDs";
  Serial.println(sBar);

  displayLED(pow(2, barHumidity) -1);

  delay(10000); // display the humidity LEDs on-board for 10 seconds
}

void displayLED(int lednumber) {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, lednumber);
  digitalWrite(latchPin, HIGH);
}

// Sleep and Wakup functions
void goToSleep() {
  ESP.deepSleep(SLEEP_INTERVAL_DURATION, WAKE_RF_DISABLED);
}

// WiFi functions
void eraseWiFiCredentials() {
  WiFi.disconnect(true);
  ESP.eraseConfig();
  willEraseWiFiCredentials = false;
}

void enableWiFi() {
  WiFi.forceSleepWake(); // wakeup WiFi modem
  delay(1);
}

void disableWiFi() {
  WiFi.mode(WIFI_OFF);
  WiFi.forceSleepBegin();
  delay(1);
}

bool connectToWiFi(bool useCredsFromFlash) {

  if (useCredsFromFlash){
    WiFi.begin();
  } else{
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
  }


  int count = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);

    if (++count % 10 == 0) {
      debugPrintln(".");
    } else {
      debugPrint(".");
    }

    if (count >= MAX_WIFI_RECONNECT_INTERVAL) {
      if (count % 10 != 0){
        debugPrintln("");
      }
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
  WiFi.mode(WIFI_AP);
  WiFi.softAP(createAPName().c_str(), WiFiAPPSK);
}

String createAPName() {
  uint8_t mac[WL_MAC_ADDR_LENGTH];
  WiFi.softAPmacAddress(mac);
  String macID = String(mac[WL_MAC_ADDR_LENGTH - 2], HEX) +
                 String(mac[WL_MAC_ADDR_LENGTH - 1], HEX);
  macID.toUpperCase();
  return AP_NamePrefix + macID;
}

void startServer() {
  server.on("/", handleRoot);

  const char * headerkeys[] = {"User-Agent","Cookie"} ;
  size_t headerkeyssize = sizeof(headerkeys)/sizeof(char*);

  server.collectHeaders(headerkeys, headerkeyssize );
  server.begin();

  isAPWebServerRunning = true;
}

void handleRoot() {
  if (server.hasArg("ssid") && server.hasArg("password") && server.hasArg("key")){
    String receivedSSID = server.arg("ssid");

    debugPrintln("[INFO] WiFi SSID received: " + receivedSSID);
    receivedSSID.toCharArray(ssid, 50);

    debugPrintln("[INFO] WiFi password received");
    server.arg("password").toCharArray(password, 50);

    debugPrintln("[INFO] IFTTT key received!");
    // writeKey(server.arg("key"));

    returnSuccessPage();
    delay(1000);

    bool hasConectedToWifi = connectToWiFi(false);

    if (!hasConectedToWifi) {
      Serial.println("[ERROR] Cannot connect to WiFi after AP mode!");
      server.sendHeader("Location","/");
      server.sendHeader("Cache-Control","no-cache");
      server.sendHeader("Set-Cookie","ESPSESSIONID=1");
      server.send(301);
      return;
    }

    debugPrintln("[INFO] Connected to WiFi after AP mode!");

    isAPWebServerRunning = false;
    return;
  }

  returnConfigPage();
}

void returnConfigPage() {
  String content = "<html><body><form action='/' method='post'>";

  content += "<h1>Welcome to Cactus@Hutscape</h1>";
  content += "<p>WiFi SSID: <input type='text' name='ssid' placeholder='ssid'></p>";
  content += "<p>WiFi Password:<input type='password' name='password' placeholder='secret'></p>";

  content += "<p>IFTTT Key:<input type='text' name='key' placeholder='IFTTT Key'></p>";
  // IFTTT key from https://ifttt.com/services/maker_webhooks/settings
  // https://maker.ifttt.com/use/{key}

  content += "<input type='submit' name='submit' value='Submit'></form></body></html>";
  server.send(200, "text/html", content);
}

void returnSuccessPage() {
  String content = "<html><body><h1>Received!</h1></body></html>";
  server.send(301, "text/html", content);
}
