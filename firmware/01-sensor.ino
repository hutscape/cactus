// INFO: Display humidity and temperature every second
// Hardware: nodeMCU with Si7021 Adafruit breakout board
// Arduino IDE Tools settings:
// Board: NodeMCU board ESP-12E
// Flash size: 4M
// CPU Frequency: 80MHz
// Upload speed: 115200
// Port: /dev/cu.wchusbserial1410

#include <SI7021.h>

#define SDA 0 // GPIO0 on ESP-01 module, D3 on nodeMCU WeMos
#define SCL 2 // GPIO2 on ESP-01 module, D4 on nodeMCU WeMos

SI7021 sensor;

void setup() {
  Serial.begin(115200);
  sensor.begin(SDA,SCL);
}

void loop() {
  int temperature = sensor.getCelsiusHundredths();
  int humidity = sensor.getHumidityPercent();
  String sTemperature = "Temperature: " + String(temperature/100)+ "°C";
  String sHumidity = "Humidity: " + String(humidity) + " %RH";

  Serial.println(sTemperature);
  Serial.println(sHumidity);
  Serial.println("");

  delay(2000);
}
