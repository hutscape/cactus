#define EN 2 // GPIO02 on ESP-01 module, D4 on nodeMCU WeMos

int dataPin = 13; // pin D7 `GPIO13` on NodeMCU boards
int clockPin = 14; // pin D5 `GPIO14` on NodeMCU boards
int latchPin = 15; // pin D8 `GPIO15` on NodeMCU boards

void setup() {
  Serial.begin(115200);
  initShiftRegister();
}

void loop() {
  // Test LEDs and shift register
  displayLED(0);
  delay(500);

  displayLED(1);
  delay(500);

  displayLED(3);
  delay(500);

  displayLED(7);
  delay(500);

  displayLED(15);
  delay(500);

  displayLED(31);
  delay(500);
}

void initShiftRegister() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  pinMode(EN, OUTPUT);
  digitalWrite(EN, LOW);
}

void displayLED(int lednumber) {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, lednumber);
  digitalWrite(latchPin, HIGH);
  Serial.println(lednumber);
}
