// INFO: Display humidity and temperature every second

// Hardware: nodeMCU with Si7021 Adafruit breakout board
// - `VIN` on si7021 and `3V3` on nodeMCU
// - `GND` on si7021 and `G` on nodeMCU
// - `SDA` on si7021 and `D2` on nodeMCU
// - `SCL` on si7021 and `D1` on nodeMCU

// IDE: Arduino Tools settings
// - Board: NodeMCU board ESP-12E
// - Flash size: 4M
// - CPU Frequency: 80MHz
// - Upload speed: 115200
// - Port: /dev/cu.wchusbserial1410

#include <SI7021.h>

#define SDA 4 // GPIO4 on ESP-01 module, D2 on nodeMCU WeMos
#define SCL 5 // GPIO5 on ESP-01 module, D1 on nodeMCU WeMos

SI7021 sensor;

void setup() {
  Serial.begin(115200);
  sensor.begin(SDA, SCL);
}

void loop() {
  int temperature = sensor.getCelsiusHundredths();
  int humidity = sensor.getHumidityPercent();
  String sTemperature = "Temperature: " + String(temperature/100)+ "°C";
  String sHumidity = "Humidity: " + String(humidity) + " RH%";

  Serial.println(sTemperature);
  Serial.println(sHumidity);
  Serial.println("");

  delay(2000);
}
