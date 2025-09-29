#include "encoder_reader.h"

void setup() {
  Serial.begin(115200);
  initEncoder(2, 3, 600);  // pins A, B and pulses per revolution
}

void loop() {
  EncoderData enc = getEncoderData();
  Serial.print("Count: "); Serial.print(enc.count);
  Serial.print(" | Dir: "); Serial.print(enc.directionForward ? "FWD" : "REV");
  Serial.print(" | Rev/s: "); Serial.print(enc.revPerSec, 2);
  Serial.print(" | Angle: "); Serial.print(enc.angle, 1);
  Serial.println(" deg");
  delay(200);
}
