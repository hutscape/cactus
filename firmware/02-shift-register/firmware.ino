// INFO: Display LED as a bar graph going from 1 LED ON to all 5 LEDs ON
// WIRING: See schematic.png

#define EN 2 // GPIO02 on ESP-01 module, D4 on nodeMCU WeMos

int latchPin = 15; // pin D8 on NodeMCU boards
int clockPin = 14; // pin D5 on NodeMCU boards
int dataPin = 13; // pin D7 on NodeMCU boards

void setup() {
  pinMode(EN, OUTPUT);

  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  Serial.begin(115200);
}

void loop() {
  digitalWrite(EN, HIGH); // enable

  display(2); // binary 10: LED 1 ON
  display(6); // binary 110: LED 1, 2 ON
  display(14); // binary 1110: LED 1, 2, 3 ON
  display(30); // binary 11110: LED 1, 2, 3, 4 ON
  display(62); // binary 111110: LED 1, 2, 3, 4, 5 ON

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
