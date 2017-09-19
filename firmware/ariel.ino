// INFO: Display humidity in a bar graph LED
// WIRING: See schematic.png

#include <SI7021.h>
#include <ESP8266WiFi.h>
#include <EEPROM.h>

extern "C" {
  #include "user_interface.h"
}

// Edit "secret" ssid and password below
const char* ssid = "secret";
const char* password = "secret";

// Set IFTTT Key from https://ifttt.com/services/maker_webhooks/settings
String iftttKey = "secret";
const char* host = "maker.ifttt.com";
const int httpsPort = 443;
const int sleepTime = 10; // 10 seconds
const int displayTime = 10; // 10 seconds

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

void setup() {
  EEPROM.begin(512);
  Serial.begin(115200);

  pinMode(EN, OUTPUT);
  digitalWrite(EN, LOW);

  pinMode(LED, OUTPUT);
  blink(3);

  Serial.print("[INFO] Reset reason:");
  Serial.println(getResetReason());

  if (CURRENT_SLEEP_INTERVAL > FINAL_SLEEP_INTERVAL) {
    resetSleepInterval();

    initialise();
    senseAndSend();

    goToSleep();
  } else {
    increaseSleepInterval();
    goToSleep();
  }
}

void loop() { }

void senseAndSend() {
  int temperature = getTemperature();
  int humidity = getHumidity();

  displayHumidity(humidity);
  sendToIFTTT(humidity, temperature);
}

void blink(int times) {
  for (int i=0; i <= times; i++){
    Serial.print("Blink ");
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

void connectWiFi() {
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("[INFO] WiFi connected");

  Serial.print("[INFO] IP address: ");
  Serial.println(WiFi.localIP());
}

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

void sendToIFTTT(int humidity, int temperature) {
  WiFiClientSecure client;
  String postData = "?value1=" + String(humidity) + "&value2=" + String(temperature);

  if (!client.connect(host, httpsPort)) {
    Serial.println("[ERROR] Connection failed");
    return;
  }

  String url = "/trigger/read_humidity/with/key/" + iftttKey + postData;

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
