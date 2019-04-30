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
#define SLEEP_DURATION 10e6
#define SLEEP_DURATION_ENGLISH "10 seconds"

int dataPin = 13; // pin D7 `GPIO13` on NodeMCU boards
int clockPin = 14; // pin D5 `GPIO14` on NodeMCU boards
int latchPin = 15; // pin D8 `GPIO15` on NodeMCU boards

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

ESP8266WebServer server(80);

Adafruit_Si7021 sensor = Adafruit_Si7021();

void setup() {
  EEPROM.begin(512);
  Serial.begin(115200);
  while(!Serial) { }

  initReadingBatteryVoltage();
  initShiftRegister();
  initTempHumiditySensor();

  if (!hasWiFiCredentials()) {
    initAccessPoint();
  }
}

void loop() {
  Serial.println();
  SensorValues s = displayTempHumidity();

  if (!hasWiFiCredentials()) {
    Serial.println("[INFO] WiFi is not configured!");
    Serial.println("[INFO] Connect to SSID 'Cactus NNNN'");
    // FIXME: Fix startMDNS();
    // Serial.println("Go to http://cactus.local/");
    Serial.println("[INFO] Go to http://192.168.4.1/");
    server.handleClient();
    delay(5000);
    return;
  }

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
  sendToIFTTT(s, getBatteryVoltage());
  delay(10000); // display the humidity LEDs on-board for 10 seconds
  goToSleep();
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

void initAccessPoint() {
  Serial.print("[TRACE] Configuring access point");
  WiFi.mode(WIFI_AP);

  String AP_NameString = getAPName();

  // convert String to char array
  char AP_NameChar[AP_NameString.length() + 1];
  memset(AP_NameChar, 0, AP_NameString.length() + 1);

  for (int i=0; i<AP_NameString.length(); i++)
    AP_NameChar[i] = AP_NameString.charAt(i);

  WiFi.softAP(AP_NameChar, WiFiAPPSK);

  // FIXME: Uncomment below to fix error message
  // startMDNS();
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

float getBatteryVoltage() {
  unsigned int raw = analogRead(A0);
  float volt = raw / 1023.0;
  volt *= 4.2;

  Serial.print("[INFO] Current voltage is ");
  Serial.print(volt);
  Serial.println("V");

  return volt;
}

void displayLED(int lednumber) {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, lednumber);
  digitalWrite(latchPin, HIGH);
}

SensorValues displayTempHumidity(void) {
  SensorValues sensorValues = {
    sensor.readTemperature(),
    sensor.readHumidity()
  };

  Serial.print("[INFO] Temperature: ");
  Serial.print(sensorValues.temperature);
  Serial.print(" °C\tHumidity: ");
  Serial.print(sensorValues.humidity);
  Serial.print(" RH%");

  int barHumidity = sensorValues.humidity/20 + 1;
  String sBar = "\tGraph: " + String(barHumidity) + " LEDs";
  Serial.println(sBar);

  displayLED(pow(2, barHumidity) -1);

  return sensorValues;
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

void goToSleep() {
  Serial.println();
  Serial.println("[INFO] Going to sleep for " + String(SLEEP_DURATION_ENGLISH));
  Serial.println("[INFO] Sleeping in 3");
  delay(1000);
  Serial.println("[INFO] Sleeping in 2");
  delay(1000);
  Serial.println("[INFO] Sleeping in 1");
  delay(1000);

  ESP.deepSleep(SLEEP_DURATION, WAKE_RF_DEFAULT);
}

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

int formatFloatToInt(float value) {
  return (int)round(value);
}

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
