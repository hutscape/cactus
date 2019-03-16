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

  digitalWrite(EN, LOW); // enable
  display(31); // Display all 5 LEDs: 11111 (binary), 31 (decimal)
}

void loop() {
}

int display(int position) {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, position);
  digitalWrite(latchPin, HIGH);
  Serial.println(position);
}
