#include <Arduino.h>

void setup() {
  Serial.begin(921600);
  Serial.println("Setup");
}

void loop() {
  delay(1000);
  Serial.println("Loop");
}
