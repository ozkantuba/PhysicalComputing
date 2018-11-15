
// These constants won't change.  They're used to give names
// to the pins used:
const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
const int analogOutPin = 9; // Analog output pin that the LED is attached to

int potentiometer = 0;        // value read from the pot

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
}

void loop() {
  // read the analog in value:
  potentiometer = analogRead(analogInPin);
  int mappedPot = map(potentiometer, 0, 1023, 0, 255); // remap the pot value to fit in 1 byte

  Serial.print("B");
  Serial.print(mappedPot);
  Serial.print("E");
 
  // wait 2 milliseconds before the next loop
  // for the analog-to-digital converter to settle
  // after the last reading:
  delay(1000);
}
