#include "Adafruit_Si7021.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <EEPROM.h>

#define EN 2 // GPIO02 on ESP-01 module, D4 on nodeMCU WeMos, or on-board LED
#define LED 2

int dataPin = 13; // pin D7 `GPIO13` on NodeMCU boards
int clockPin = 14; // pin D5 `GPIO14` on NodeMCU boards
int latchPin = 15; // pin D8 `GPIO15` on NodeMCU boards

String AP_NamePrefix = "Cactus ";
const char WiFiAPPSK[] = "hutscape";
const char* DomainName = "cactus"; // set domain name domain.local
char ssid [50] = "";
char password [50] = "";

String key = "";
// IFTTT key from https://ifttt.com/services/maker_webhooks/settings
// https://maker.ifttt.com/use/{key}

const char* host = "maker.ifttt.com";
const int httpsPort = 443;

ESP8266WebServer server(80);

Adafruit_Si7021 sensor = Adafruit_Si7021();

void setup() {
  WiFi.disconnect();
  EEPROM.begin(512);
  Serial.begin(115200);
  while(!Serial) { }

  pinMode(A0, INPUT); // read battery levels

  initShiftRegister();
  initTempHumiditySensor();

  if (!hasWiFiCredentials()) {
    initAccessPoint();
  }
}

void loop() {
  displayTempHumidity();
  displayBattery();

  if (!hasWiFiCredentials()) {
    Serial.println("[INFO] WiFi is not configured!");
    Serial.println("[INFO] Connect to SSID 'Cactus NNNN'");
    // FIXME: Fix startMDNS();
    // Serial.println("Go to http://cactus.local/");
    Serial.println("Go to http://192.168.4.1/");
    server.handleClient();
    blink(30); // Give the user (30*2) 60 seconds to put in the WiFi creds
  } else {
    if (connectToWiFi() == true) {
      Serial.print("[INFO] WiFi is connected: ");
      Serial.println(WiFi.SSID());
      sendToIFTTT();
    } else {
      Serial.print("[ERROR] WiFi is not connected: ");
    }
    delay(30000); // display the humidity values on-board for 30 seconds
  }

  goToSleep();
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

void displayLED(int lednumber) {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, lednumber);
  digitalWrite(latchPin, HIGH);
}

void displayTempHumidity(void) {
  Serial.print("[INFO] Temperature: ");
  Serial.print(sensor.readTemperature());
  Serial.print(" °C\tHumidity: ");
  Serial.print(sensor.readHumidity());
  Serial.print(" RH%");

  int barHumidity = sensor.readHumidity()/20 + 1;
  String sBar = "\tGraph: " + String(barHumidity) + " LEDs";
  Serial.println(sBar);

  displayLED(pow(2, barHumidity) -1);
}

void displayBattery(void) {
  Serial.print("[INFO] Battery: ");

  unsigned int raw = analogRead(A0);
  float volt = raw / 1023.0;
  volt = volt * 4.2;

  String v = String(volt);
  Serial.println(raw);
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
    Serial.print("[INFO] SSID received: ");
    Serial.println(server.arg("ssid"));
    server.arg("ssid").toCharArray(ssid, 50);

    Serial.print("[INFO] Password received");
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

      if (count > 120) {
        Serial.println("[ERROR] Could not connect to WiFi. Please try again.");
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

  content += "WiFi SSID: <input type='text' name='ssid' placeholder='ssid'><br>";
  content += "WiFi Password:<input type='password' name='password' placeholder='secret'><br>";

  content += "IFTTT Key:<input type='text' name='key' placeholder='IFTTT Key'><br>";
  // Get the "secret" from https://ifttt.com/services/maker_webhooks/settings

  content += "<input type='submit' name='submit' value='Submit'></form></body></html>";
  server.send(200, "text/html", content);
}

void goToSleep() {
  Serial.println("");
  Serial.println("[INFO] Sleeping in 2");
  delay(100);
  Serial.println("[INFO] Sleeping in 1");
  delay(100);

  ESP.deepSleep(0, WAKE_RF_DEFAULT);
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

  // TODO: Store length of key
  for (int i = 0; i < 22; ++i) {
    readChar = char(EEPROM.read(i));
    readStr += readChar;
  }

  return readStr;
}

void sendToIFTTT() {
  Serial.println("[INFO] Sending IFTTT notification...");
  WiFiClientSecure client;

  if (!client.connect(host, httpsPort)) {
    Serial.println("[ERROR] Connection failed");
    return;
  }

  String url = "/trigger/cactus_values/with/key/";
  key = readKey();

  client.print(String("POST ") + url + key + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "User-Agent: ESP8266\r\n" +
               "Connection: close\r\n\r\n");

  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println("[ERROR] Client Timeout!");
      client.stop();
      return;
    }
  }

  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }

  return;
}
