#include <MotorEncoder.h>

MotorEncoder encoder;

void setup() {
  Serial.begin(115200);
  encoder.begin(2, 3, 600, 0, 100.0, 300, false, true); 
}

void loop() {
  EncoderData data = encoder.read();

  Serial.print("Ticks: "); Serial.print(data.tickCount);
  Serial.print(" | Shaft RPM: "); Serial.print(data.shaftRPM, 2);
  Serial.print(" | Angle: "); Serial.print(data.shaftAngleDeg, 1);
  Serial.print(" | Output RPM: "); Serial.print(data.outputRPM, 2);
  Serial.print(" | Wheel Speed: "); Serial.print(data.wheelSpeed_mps, 2);
  Serial.print(" m/s ("); Serial.print(data.wheelSpeed_kmph, 2); Serial.print(" km/h)");
  Serial.print(" | Dir: "); Serial.println(data.directionForward ? "FWD" : "REV");

  delay(500);
}
