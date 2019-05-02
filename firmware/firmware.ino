#include <math.h>
#include "Adafruit_Si7021.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <EEPROM.h>

#define EN 2 // GPIO02 on ESP-01 module, D4 on nodeMCU WeMos, or on-board LED
#define LED 2
#define BATTERY_VOLT A0
#define USERBUTTON 12 // GPIO012 on ESP or D6 on WeMos

// Sleep
#define SLEEP_INTERVAL_DURATION  10e6 // 10 seconds
#define FINAL_SLEEP_INTERVAL_COUNT 3 // 3*10 seconds = 30 seconds
#define SLEEP_DURATION_ENGLISH "30 seconds"
#define CURRENT_SLEEP_INTERVAL_ADDR 30 // EEPROM address to store sleep interval
#define CURRENT_SLEEP_INTERVAL_COUNT EEPROM.read(CURRENT_SLEEP_INTERVAL_ADDR)

// LEDs and shift register
int dataPin = 13; // pin D7 `GPIO13` on NodeMCU boards
int clockPin = 14; // pin D5 `GPIO14` on NodeMCU boards
int latchPin = 15; // pin D8 `GPIO15` on NodeMCU boards

// WiFi
String AP_NamePrefix = "Cactus ";
const char WiFiAPPSK[] = "hutscape";
const char* DomainName = "cactus"; // set domain name domain.local
char ssid [50] = "";
char password [50] = "";

const char* host = "maker.ifttt.com";
const int httpsPort = 443;
const int httpPort = 80;

// Get fingerprint of maker.ifttt.com
// echo | openssl s_client -connect maker.ifttt.com:443 |& openssl x509 -fingerprint -noout
const char fingerprint[] PROGMEM = "AA:75:CB:41:2E:D5:F9:97:FF:5D:A0:8B:7D:AC:12:21:08:4B:00:8C";

struct SensorValues {
  float temperature;
  float humidity;
};

int userButtonValue;

ESP8266WebServer server(80);

Adafruit_Si7021 sensor = Adafruit_Si7021();

void setup() {
  // TODO: Wakeup without radio and check if 4 hours is up
  // if not increase counter and sleep

  userButtonValue = digitalRead(USERBUTTON);

  EEPROM.begin(512);
  initSerial();

  // NOTE: If sleep interval is not up and user has not pressed button,
  // Then increase the counter and go back to sleep
  if (!isCurrentSleepIntervalOver() && !hasUserPressedButton(userButtonValue)) {
    increaseSleepInterval();

    if (isNextSleepIntervalOver()) {
      goToSleep(true);
    } else {
      goToSleep(false);
    }
  }

  // NOTE: If the user presses the button,
  // then the humidity level will be displayed in the LEDs
  if (hasUserPressedButton(userButtonValue)) {
    initShiftRegister();
  }

  initReadingBatteryVoltage();
  initTempHumiditySensor();
  resetSleepInterval();

  if (!hasWiFiCredentials()) {
    initAccessPoint();
  }
}

void loop() {
  Serial.println();
  SensorValues sensorValues = readTempHumidity();

  if (hasUserPressedButton(userButtonValue)) {
    displayHumidity(sensorValues.humidity);
  }

  if (!hasWiFiCredentials()) {
    Serial.println("[INFO] WiFi is not configured!");
    Serial.println("[INFO] Connect to SSID 'Cactus NNNN'");

    Serial.println("[INFO] Go to http://cactus.local");
    server.handleClient();
    delay(5000);
    return;
  }

  // FIXME 2: Goes into this mode sometimes on user button press
  if (!connectToWiFi()) {
    Serial.print("[ERROR] WiFi cannot be connected with SSID ");
    Serial.println(WiFi.SSID());
    eraseWiFiCredentials();
    Serial.println("[INFO] Connect to SSID 'Cactus NNNN' to re-configure WiFI.");
    delay(5000);
    return;
  }

  Serial.print("[INFO] WiFi is connected: ");
  Serial.println(WiFi.SSID());

  // FIXME: Uncomment below after completing FIXME 2
  Serial.println("[INFO] Sending to IFTTT");
  // sendToIFTTT(sensorValues, getBatteryVoltage());

  goToSleep(false);
}

// Wakeup and sleep
bool isCurrentSleepIntervalOver() {
  if (CURRENT_SLEEP_INTERVAL_COUNT < FINAL_SLEEP_INTERVAL_COUNT) {
    return false;
  }

  return true;
}

bool isNextSleepIntervalOver() {
  if (CURRENT_SLEEP_INTERVAL_COUNT == FINAL_SLEEP_INTERVAL_COUNT) {
    return true;
  }

  return false;
}

void goToSleep(bool hasWiFiWhenAwake) {
  Serial.println("[INFO] Going back to sleep to complete " + String(SLEEP_DURATION_ENGLISH));
  Serial.println("[INFO] Sleeping in 3");
  delay(500);
  Serial.println("[INFO] Sleeping in 2");
  delay(500);
  Serial.println("[INFO] Sleeping in 1");
  delay(500);

  if (hasWiFiWhenAwake) {
    ESP.deepSleep(SLEEP_INTERVAL_DURATION, WAKE_RF_DEFAULT);
  } else {
    ESP.deepSleep(SLEEP_INTERVAL_DURATION, WAKE_RF_DISABLED);
  }
}

void resetSleepInterval() {
  printSleepInterval();

  Serial.print("[INFO] Reset sleep interval coz ");
  Serial.print(SLEEP_DURATION_ENGLISH);
  Serial.println(" is up or user pressed button!");

  EEPROM.write(CURRENT_SLEEP_INTERVAL_ADDR, 0);
  EEPROM.commit();
}

void increaseSleepInterval() {
  printSleepInterval();

  EEPROM.write(CURRENT_SLEEP_INTERVAL_ADDR, CURRENT_SLEEP_INTERVAL_COUNT + 1);
  EEPROM.commit();
}

void printSleepInterval() {
  Serial.print("[INFO] Current sleep interval: ");
  Serial.print(CURRENT_SLEEP_INTERVAL_COUNT);
  Serial.print("/");
  Serial.println(FINAL_SLEEP_INTERVAL_COUNT);
}

// Sensors
void initSerial() {
  Serial.begin(115200);
  while(!Serial) { }
  Serial.println();
}

bool hasUserPressedButton(int userButtonValue) {
  if (userButtonValue == 0) {
    Serial.println("[INFO] User pressed button!");
    return true;
  }

  Serial.println("[INFO] Automatic wakeup!");
  return false;
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
  Serial.print(" °C\tHumidity: ");
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

// LED
void displayLED(int lednumber) {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, lednumber);
  digitalWrite(latchPin, HIGH);
}

void blink(int times) {
  Serial.print("[INFO] Wait for ");
  Serial.print(times/30);
  Serial.println(" minutes");

  int count = 0;

  while (count < times) {
    digitalWrite(LED, HIGH);
    delay(1000);
    digitalWrite(LED, LOW);
    delay(1000);

    Serial.print("[INFO] ");
    Serial.print(2*count);
    Serial.println(" seconds");

    count++;
  }
}

// Battery
float getBatteryVoltage() {
  unsigned int raw = 0;
  float volt = 0.0;
  float batteryVoltage = 0.0;

  // NOTE: Get 10 analog values and smoothen it
  for (int count = 0; count < 10; count++) {
    raw = analogRead(A0);
    volt = raw / 1023.0;
    volt *= 4.2;

    batteryVoltage += volt;
  }

  batteryVoltage /= 10;

  Serial.print("[INFO] Current voltage is ");
  Serial.print(batteryVoltage);
  Serial.println("V");

  return volt;
}

// EEPROM
void writeKey(String writeStr) {
  delay(10);

  for (int i = 0; i < writeStr.length(); ++i) {
    EEPROM.write(i, writeStr[i]);
  }

  EEPROM.commit();
}

String readKey() {
  String readStr;
  char readChar;

  for (int i = 0; i < 22; ++i) {
    readChar = char(EEPROM.read(i));
    readStr += readChar;
  }

  return readStr;
}

// WiFi
void initAccessPoint() {
  // TODO: Blink LED to indicate that user has to put in the credentials in AP mode
  Serial.println("[INFO] Configuring access point");
  WiFi.mode(WIFI_AP);

  String AP_NameString = getAPName();

  // convert String to char array
  char AP_NameChar[AP_NameString.length() + 1];
  memset(AP_NameChar, 0, AP_NameString.length() + 1);

  for (int i=0; i<AP_NameString.length(); i++)
    AP_NameChar[i] = AP_NameString.charAt(i);

  WiFi.softAP(AP_NameChar, WiFiAPPSK);

  startMDNS();
  startServer();
  Serial.print("[INFO] Started access point at IP ");
  Serial.println(WiFi.softAPIP());
}

bool connectToWiFi() {
  int count = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    count++;

    if (count % 10 == 0) {
      Serial.println("");
    }

    if (count > 120) {
      Serial.println("[ERROR] Could not connect to WiFi. Please try again.");
      return false;
    }
  }

  return true;
}

void eraseWiFiCredentials() {
  WiFi.disconnect(true);
  ESP.eraseConfig();
  Serial.println("[INFO] WiFi credentials are erased.");
  Serial.print("[INFO] Read WiFi SSID (should be empty): ");
  Serial.println(WiFi.SSID());
}

bool hasWiFiCredentials() {
  if (WiFi.SSID() == "") {
    return false;
  }

  return true;
}

String getAPName() {
  uint8_t mac[WL_MAC_ADDR_LENGTH];
  WiFi.softAPmacAddress(mac);
  String macID = String(mac[WL_MAC_ADDR_LENGTH - 2], HEX) +
                 String(mac[WL_MAC_ADDR_LENGTH - 1], HEX);
  macID.toUpperCase();
  return AP_NamePrefix + macID;
}

void startMDNS() {
  if (!MDNS.begin(DomainName)) {
    Serial.println("[ERROR] MDNS responder did not setup");
    while(1) {
      delay(1000);
    }
  }

  MDNS.addService("http", "tcp", 80);
}

void startServer() {
  server.on("/", handleRoot);

  const char * headerkeys[] = {"User-Agent","Cookie"} ;
  size_t headerkeyssize = sizeof(headerkeys)/sizeof(char*);

  server.collectHeaders(headerkeys, headerkeyssize );
  server.begin();
}

void handleRoot() {
  if (server.hasArg("ssid") && server.hasArg("password") && server.hasArg("key")){
    Serial.print("[INFO] WiFi SSID received: ");
    Serial.println(server.arg("ssid"));
    server.arg("ssid").toCharArray(ssid, 50);

    Serial.println("[INFO] WiFi password received");
    server.arg("password").toCharArray(password, 50);

    Serial.println("[INFO] IFTTT key received!");
    writeKey(server.arg("key"));

    WiFi.begin(ssid, password);
    WiFi.persistent(true);
    WiFi.setAutoConnect(true);
    WiFi.setAutoReconnect(true);

    int count = 0;
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
      count++;

      if (count % 10 == 0) {
        Serial.println("");
      }

      if (count > 120) { // Will try to connect to the WiFI for 120 seconds
        Serial.println("[ERROR] Could not connect to WiFi. Please try again.");
        // TODO: What happens if the WiFi credentials are not correct?
        // TODO: What happens if user wants to use it without the Internet?
        WiFi.disconnect();
        initAccessPoint();
        break;
      }
    }

    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("");
      Serial.print("[INFO] WiFi connected! IP address: ");
      Serial.println(WiFi.localIP());

      server.sendHeader("Location","/");
      server.sendHeader("Cache-Control","no-cache");
      server.sendHeader("Set-Cookie","ESPSESSIONID=1");
      server.send(301);

      return;
    }
  }

  String content = "<html><body><form action='/' method='post'>";

  content += "<h1>Welcome to Cactus@Hutscape</h1>";
  content += "<p>WiFi SSID: <input type='text' name='ssid' placeholder='ssid'></p>";
  content += "<p>WiFi Password:<input type='password' name='password' placeholder='secret'></p>";

  content += "<p>IFTTT Key:<input type='text' name='key' placeholder='IFTTT Key'></p>";
  // IFTTT key from https://ifttt.com/services/maker_webhooks/settings
  // https://maker.ifttt.com/use/{key}

  // TODO: A checkbox to use with / without the Internet
  // TODO: Wakeup when button pressed to read the humidity values on-board

  content += "<input type='submit' name='submit' value='Submit'></form></body></html>";
  server.send(200, "text/html", content);
}

// Cloud
void sendToIFTTT(SensorValues sensorValues, float batteryVoltage) {
  Serial.println("[INFO] Sending IFTTT notification...");

  WiFiClientSecure client;
  client.setFingerprint(fingerprint);

  if (!client.connect(host, httpsPort)) {
    Serial.println("[ERROR] Connection failed");
    return;
  }

  Serial.println("[INFO] Client connected");

  String url = "/trigger/cactus_values/with/key/";
  url += readKey();

  char data[34];
  sprintf(data, "value1=%03d&value2=%03d&value3=%2.1f", formatFloatToInt(sensorValues.temperature), formatFloatToInt(sensorValues.humidity), batteryVoltage);

  Serial.print("[INFO] Data sent: ");
  Serial.println(data);
  Serial.print("[INFO] Data size: ");
  Serial.println(sizeof(data));

  client.println(String("POST ") + url + " HTTP/1.1");
  client.println(String("Host: ") + host);
  client.println(String("Content-Type: application/x-www-form-urlencoded"));
  client.print(String("Content-Length: "));
  client.println(sizeof(data));
  client.println();
  client.println(data);

  Serial.println("[INFO] Client posted");

  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 20000) {
      Serial.println("[ERROR] Client Timeout!");
      client.stop();
      return;
    }
  }

  Serial.println("[INFO] Reply from client:");
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }

  client.stop();
  return;
}

// Others
int formatFloatToInt(float value) {
  return (int)round(value);
}
