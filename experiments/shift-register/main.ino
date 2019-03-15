#define EN 2 // GPIO02 on ESP-01 module, D4 on nodeMCU WeMos

int dataPin = 13; // pin D7 `GPIO13` on NodeMCU boards
int clockPin = 14; // pin D5 `GPIO14` on NodeMCU boards
int latchPin = 15; // pin D8 `GPIO15` on NodeMCU boards
long randNumber;

void setup() {
  pinMode(EN, OUTPUT);

  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  Serial.begin(115200);
}

void loop() {
  digitalWrite(EN, HIGH); // enable
  display(31); // All 5 LEDs are on: 31 (dec) is 11111 (bin)
  digitalWrite(EN, LOW); // disable
  delay(5000); // LED off for 5 seconds
}

int display(int position) {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, position);
  digitalWrite(latchPin, HIGH);
  Serial.println(position);
  delay(500);
}
