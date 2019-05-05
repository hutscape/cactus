void setup() {
  pinMode(2, OUTPUT); // GPIO02 on ESP-12 module is linked to on-board LED
  Serial.begin(115200);
  Serial.println("setup");
}

void loop() {
  digitalWrite(2, HIGH);
  Serial.println("HIGH");
  delay(1000);
  digitalWrite(2, LOW);
  Serial.println("LOW");
  delay(1000);
}
