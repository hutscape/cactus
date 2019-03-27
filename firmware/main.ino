// INFO: Display humidity in a bar graph LED
// WIRING: See schematic.png

#include <SI7021.h>
#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

extern "C" {
  #include "user_interface.h"
}

const char* host = "maker.ifttt.com";
const int httpsPort = 443;
const int sleepTime = 10; // 10 seconds
const int displayTime = 10; // 10 seconds

String AP_NamePrefix = "Cactus ";
const char WiFiAPPSK[] = "underthesea";
const char* DomainName = "cactus";
char ssid [50] = "";
char password [50] = "";
String key = "";

#define LED 2
#define SDA 4 // GPIO4 on ESP-01 module, D2 on nodeMCU WeMos
#define SCL 5 // GPIO5 on ESP-01 module, D1 on nodeMCU WeMos
#define EN 2 // GPIO02 on ESP-01 module, D4 on nodeMCU WeMos

#define FINAL_SLEEP_INTERVAL 6 // 6 * sleepTime = 6 hours
#define CURRENT_SLEEP_INTERVAL_ADDR 30 // EEPROM address to store sleep interval
#define CURRENT_SLEEP_INTERVAL EEPROM.read(CURRENT_SLEEP_INTERVAL_ADDR)

int dataPin = 13; // pin D7 on NodeMCU boards
int clockPin = 14; // pin D5 on NodeMCU boards
int latchPin = 15; // pin D8 on NodeMCU boards

SI7021 sensor;
ESP8266WebServer server(80);

void setup() {
  EEPROM.begin(512);
  Serial.begin(115200);

  pinMode(EN, OUTPUT);
  digitalWrite(EN, LOW);

  pinMode(LED, OUTPUT);
  blink(3);

  // TODO: When button is pressed, always senseAndSend()
  if (!hasWiFiCredentials()) {
    setupAP();
  } else {
    if (CURRENT_SLEEP_INTERVAL > FINAL_SLEEP_INTERVAL) {
      resetSleepInterval();
      initialise();
    } else {
      increaseSleepInterval();
      goToSleep();
    }
  }
}

void loop() {
  if (!hasWiFiCredentials()) {
    blink(200);
    Serial.println("[INFO] WiFi is not configured!");
    Serial.println("[INFO] Connect to 'Cactus XXX' WiFi and visit http://cactus.local/");
    server.handleClient();
  } else {
    blink(2000);

    if (connectWiFi() == true) {
      senseAndSend();
    }

    goToSleep();
  }
}

// common
void blink(int times) {
  for (int i=0; i <= times; i++){
    Serial.print("[INFO] Blink ");
    Serial.println(i);

    digitalWrite(2, HIGH);
    delay(1000);

    digitalWrite(2, LOW);
    delay(1000);
  }
}

void initialise() {
  Serial.println("[INFO] Wake up!");

  sensor.begin(SDA,SCL);

  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  connectWiFi();
}

// WiFi
bool connectWiFi() {
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

bool hasWiFiCredentials() {
  if (WiFi.SSID() == "") {
    return false;
  }

  return true;
}

// temperature and humidity sensor
int getHumidity() {
  int humidity = sensor.getHumidityPercent();
  String sHumidity = "[INFO] Humidity: " + String(humidity) + " RH%";
  Serial.println(sHumidity);

  return humidity;
}

int getTemperature() {
  int temperature = sensor.getCelsiusHundredths() / 100;
  String sTemperature = "[INFO] Temperature: " + String(temperature)+ "°C";
  Serial.println(sTemperature);

  return temperature;
}

int displayHumidity(int humidity) {
  Serial.println("[INFO] Humidity bar LED display for 10 seconds");
  int barValue = humidity/20 + 1;

  digitalWrite(EN, LOW); // Enable Shift register
  int position = 0;

  if (barValue == 1) {
    position = 2;
  } else if (barValue == 2) {
    position = 6;
  } else if (barValue == 3) {
    position = 14;
  } else if (barValue == 4) {
    position = 30;
  } else {
    position = 62;
  }

  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, position);
  digitalWrite(latchPin, HIGH);

  delay(displayTime * 1000); // display LED for some time
  digitalWrite(EN, HIGH); // Disable Shift register
  Serial.println("[INFO] LED Display off");
}

void senseAndSend() {
  int temperature = getTemperature();
  int humidity = getHumidity();

  displayHumidity(humidity);
  sendToIFTTT(humidity, temperature);
}

void sendToIFTTT(int humidity, int temperature) {
  WiFiClientSecure client;
  String postData = "?value1=" + String(humidity) + "&value2=" + String(temperature);

  if (!client.connect(host, httpsPort)) {
    Serial.println("[ERROR] Connection failed");
    return;
  }

  String url = "/trigger/read_humidity/with/key/" + key + postData;

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
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

  Serial.println("");
  Serial.println("[INFO] Closing connection");
  return;
}

// deep sleep related function
void resetSleepInterval() {
  Serial.println("[INFO] Reset sleep interval");
  EEPROM.write(CURRENT_SLEEP_INTERVAL_ADDR, 0);
  EEPROM.commit();
}

void increaseSleepInterval() {
  Serial.print("[INFO] Current sleep interval: ");
  Serial.println(CURRENT_SLEEP_INTERVAL);
  EEPROM.write(CURRENT_SLEEP_INTERVAL_ADDR, CURRENT_SLEEP_INTERVAL + 1);
  EEPROM.commit();
}

void goToSleep() {
  Serial.println("[INFO] Going to sleep...");
  ESP.deepSleep(sleepTime * 1000000);
}

// initial AP setup
void setupAP() {
  Serial.println("[TRACE] Configuring access point");
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

    Serial.println("[INFO] IFTTT key received!");
    writeKey(server.arg("key"));
    readKey();

    if (server.arg("key") == readKey()) {
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
  }

  String content = "<html><body><form action='/' method='post'>";
  content += "SSID: <input type='text' name='ssid' placeholder='ssid'><br>";
  content += "Password:<input type='password' name='password' placeholder='secret'><br>";
  content += "IFTTT Key:<input type='text' name='key' placeholder='IFTTT Key'><br>";
  content += "<input type='submit' name='submit' value='Submit'></form></body></html>";
  server.send(200, "text/html", content);
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
