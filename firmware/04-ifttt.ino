// INFO: Display humidity in a bar graph LED

// Hardware: nodeMCU with shift register 74hc595 and 5 LEDs
// - DS pin 14 to Digital pin D7 on nodeMCU (data pin)
// - SH_CP pin 11 to Digital pin D5 on nodeMCU (clock pin)
// - ST_CP pin 12 to Digital pin D8 on nodeMCU (latch pin)
// - GND pin 8 to GND
// - Vcc pin 16 to 5V
// - OE pin 13 to D1 on nodeMCU (control enable / disable chip)
// - MR pin 10 to 5V
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

// IDE: Arduino Tools settings
// - Board: NodeMCU board ESP-12E
// - Flash size: 4M
// - CPU Frequency: 80MHz
// - Upload speed: 115200
// - Port: /dev/cu.wchusbserial1410

#include <SI7021.h>
#include <ESP8266WiFi.h>

extern "C" {
  #include "user_interface.h"
}

// Edit "secret" ssid and password below
const char* ssid = "secret";
const char* password = "secret";
const char* host = "maker.ifttt.com";
const int httpsPort = 443;

#define SDA 0 // GPIO0 on ESP-01 module, D3 on nodeMCU WeMos
#define SCL 2 // GPIO2 on ESP-01 module, D4 on nodeMCU WeMos
#define EN 5

int latchPin = 15; // pin D8 on NodeMCU boards
int clockPin = 14; // pin D5 on NodeMCU boards
int dataPin = 13; // pin D7 on NodeMCU boards

SI7021 sensor;

void setup() {
  Serial.begin(115200);

  // initialisation
  sensor.begin(SDA,SCL);

  pinMode(EN, OUTPUT);
  digitalWrite(EN, HIGH);

  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  connectWiFi();
}

void loop() {
  int temperature = sensor.getCelsiusHundredths();
  int humidity = sensor.getHumidityPercent();
  int barHumidity = humidity/20 + 1;
  String sTemperature = "Temperature: " + String(temperature/100)+ "°C";
  String sHumidity = "Humidity: " + String(humidity) + " RH%";
  String sBar = "Graph: " + String(barHumidity) + " bars";

  Serial.println(sTemperature);
  Serial.println(sHumidity);
  Serial.println(sBar);
  Serial.println("");
  display(barHumidity);
  sendToIFTTT(humidity, temperature);

  delay(3600000); // 1 hour
}

void connectWiFi() {
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("[INFO] WiFi connected");
  Serial.println("[INFO] IP address: ");
  Serial.println(WiFi.localIP());
}

int display(int barValue) {
  digitalWrite(EN, LOW);
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

  delay(5000);
  digitalWrite(EN, HIGH);
}

void sendToIFTTT(int humidity, int temperature) {
  WiFiClientSecure client;
  String postData = "?value1=" + String(humidity) + "&value2=" + String(temperature/100);

  if (!client.connect(host, httpsPort)) {
    Serial.println("[ERROR] Connection failed");
    return;
  }

  // Get the "secret" from https://ifttt.com/services/maker_webhooks/settings
  String url = "/trigger/read_humidity/with/key/secret" + postData;

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

  Serial.println("[INFO] Closing connection");
  return;
}
