#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "secret";
const char* password = "secret";
const char* apiKey = "secret";

const char* host = "maker.ifttt.com";
const int httpsPort = 443;

extern "C" {
  #include "user_interface.h"
}

void setup() {
  Serial.begin(115200);

  delay(100);

  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("WiFi SSID: ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  Serial.println("[INFO] Sending IFTTT notification...");
  WiFiClient client;

  if (!client.connect(host, 80)) {
    Serial.println("[ERROR] Connection failed");
  }

  Serial.println("[INFO] Client connected");

  String url = "/trigger/cactus_values/with/key/";
  url += apiKey;

  Serial.print("Requesting URL: ");
  Serial.println(url);
  client.print(String("POST ") + url + " HTTP/1.1\r\n" +
    "Host: " + host + "\r\n" +
    "Content-Type: application/x-www-form-urlencoded\r\n" +
    "Content-Length: 13\r\n\r\n" +
    "value1=420&value2=2000&value3=3000" + "\r\n");
  client.stop();

  Serial.println("[INFO] Client posted");
  return;
}

void loop() {
}
