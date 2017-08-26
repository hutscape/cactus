// INFO: Display LED as a bar graph going from 1 LED ON to all 5 LEDs ON

// Hardware: nodeMCU with shift register 74hc595 and 5 LEDs
// - DS pin 14 to Digital pin D7 on nodeMCU (data pin)
// - SH_CP pin 11 to Digital pin D5 on nodeMCU (clock pin)
// - ST_CP pin 12 to Digital pin D8 on nodeMCU (latch pin)
// - GND pin 8 to GND
// - Vcc pin 16 to 5V
// - OE pin 13 to GND
// - MR pin 10 to 5V
// - pin 1 to LED and then 1kΩ resistor to GND
// - pin 2 to LED and then 1kΩ resistor to GND
// - pin 3 to LED and then 1kΩ resistor to GND
// - pin 4 to LED and then 1kΩ resistor to GND
// - pin 5 to LED and then 1kΩ resistor to GND

// IDE: Arduino Tools settings
// - Board: NodeMCU board ESP-12E
// - Flash size: 4M
// - CPU Frequency: 80MHz
// - Upload speed: 115200
// - Port: /dev/cu.wchusbserial1410

int latchPin = 15; // pin D8 on NodeMCU boards
int clockPin = 14; // pin D5 on NodeMCU boards
int dataPin = 13; // pin D7 on NodeMCU boards

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  display(2); // binary 10: LED 1 ON
  display(6); // binary 110: LED 1, 2 ON
  display(14); // binary 1110: LED 1, 2, 3 ON
  display(30); // binary 11110: LED 1, 2, 3, 4 ON
  display(62); // binary 111110: LED 1, 2, 3, 4, 5 ON
}

int display(int position) {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, position);
  digitalWrite(latchPin, HIGH);
  Serial.println(position);
  delay(500);
}
