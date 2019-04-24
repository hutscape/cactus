#include "Adafruit_Si7021.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#define EN 2 // GPIO02 on ESP-01 module, D4 on nodeMCU WeMos

int dataPin = 13; // pin D7 `GPIO13` on NodeMCU boards
int clockPin = 14; // pin D5 `GPIO14` on NodeMCU boards
int latchPin = 15; // pin D8 `GPIO15` on NodeMCU boards

String AP_NamePrefix = "Cactus ";
const char WiFiAPPSK[] = "hutscape";
const char* DomainName = "cactus"; // set domain name domain.local
char ssid [50] = "";
char password [50] = "";

ESP8266WebServer server(80);

Adafruit_Si7021 sensor = Adafruit_Si7021();

void setup() {
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
    Serial.println("[INFO] Connect to CactusXXX and go to http://cactus.local/");
    server.handleClient();

  } else {
    Serial.print("[INFO] WiFi is connected: ");
    Serial.println(WiFi.SSID());
  }

  delay(2000);
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

  startMDNS();
  startServer();
  Serial.println("[INFO] Started access point!");
}

void setupAP() {
  Serial.print("[TRACE] Configuring access point");
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
  Serial.println("[INFO] Started access point!");
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
  if (server.hasArg("ssid") && server.hasArg("password")){
    Serial.print("[INFO] SSID:");
    Serial.println(server.arg("ssid"));
    server.arg("ssid").toCharArray(ssid, 50);

    Serial.print("[INFO] Password received!");
    server.arg("password").toCharArray(password, 50);

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
        setupAP();
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
  // content += "IFTTT Key:<input type='text' name='key' placeholder='IFTTT Key'><br>";
  content += "<input type='submit' name='submit' value='Submit'></form></body></html>";
  server.send(200, "text/html", content);
}
