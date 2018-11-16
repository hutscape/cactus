// INFO: Display humidity and temperature every frequency

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
