// INFO: Display humidity in a bar graph LED

// Hardware: nodeMCU to button for interrupt
// RST to button pin 1
// D0 / GPIO16 to button pin 1
// 10k resistor to 3.3V from button pin 1
// GND to button pin 2

// Hardware: nodeMCU with shift register 74hc595 and 5 LEDs
// - DS pin 14 to Digital pin D7 on nodeMCU (data pin)
// - SH_CP pin 11 to Digital pin D5 on nodeMCU (clock pin)
// - ST_CP pin 12 to Digital pin D8 on nodeMCU (latch pin)
// - GND pin 8 to GND
// - Vcc pin 16 to 3.3V
// - OE pin 13 to the output of a Smidth Trigger to enable / disable chip
// - MR pin 10 to 3.3V
// - pin 1 to LED 1 and then 1kΩ resistor to GND
// - pin 2 to LED 2 and then 1kΩ resistor to GND
// - pin 3 to LED 3 and then 1kΩ resistor to GND
// - pin 4 to LED 4 and then 1kΩ resistor to GND
// - pin 5 to LED 5 and then 1kΩ resistor to GND

// Hardware: nodeMCU with Si7021 Adafruit breakout board
// - `VIN` on si7021 and `3V3` on nodeMCU
// - `GND` on si7021 and `G` on nodeMCU
// - `SDA` on si7021 and `D3` on nodeMCU
// - `SCL` on si7021 and `D4` on nodeMCU
// - `D0` on nodeMCU and `RST` on nodeMCU to reset for wakeup
// - `D1` on nodeMCU and input of Smidth Trigger

#include <SI7021.h>
#include <ESP8266WiFi.h>

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
const int sleepTime = 14400; // 14400 seconds = 4 hour
const int displayTime = 10; // 10 seconds

#define SDA 4 // GPIO4 on ESP-01 module, D2 on nodeMCU WeMos
#define SCL 5 // GPIO5 on ESP-01 module, D1 on nodeMCU WeMos
#define EN 2 // GPIO02 on ESP-01 module, D4 on nodeMCU WeMos

int latchPin = 15; // pin D8 on NodeMCU boards
int clockPin = 14; // pin D5 on NodeMCU boards
int dataPin = 13; // pin D7 on NodeMCU boards

SI7021 sensor;

void setup() {
  Serial.begin(115200);
  Serial.println("[INFO] Wake up!");

  // initialisation
  sensor.begin(SDA,SCL);

  pinMode(EN, OUTPUT);
  digitalWrite(EN, LOW);

  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  connectWiFi();
}

void loop() {
  int temperature = getTemperature();
  int humidity = getHumidity();

  displayHumidity(humidity);
  sendToIFTTT(humidity, temperature);

  goToSleep();
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

  digitalWrite(EN, HIGH); // Enable Shift register
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
  digitalWrite(EN, LOW); // Disable Shift register
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

void goToSleep() {
  Serial.println("[INFO] Going to sleep for 4 hours");
  ESP.deepSleep(sleepTime * 1000000);
}
