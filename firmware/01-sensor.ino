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
  String sTemperature = "Temperature: " + temperature;
  String sHumidity = "Humidity: " + humidity;

  Serial.println(temperature);
  Serial.println(humidity);

  delay(2000);
}
