#include <MotorEncoder.h>

// Create an instance of the MotorEncoder class
MotorEncoder encoder;

void setup() {
  Serial.begin(115200);

  /* ========================================================
     EXAMPLE 1: Auto-calculated Gear Ratio
     --------------------------------------------------------
     - pulsesPerRev: Number of pulses per motor shaft revolution
       (e.g., 600 for your encoder). If unknown, set 0.
     - gearRatio: Set 0 to auto-calculate based on motorRatedRPM.
     - wheelDiameter_mm: Outer diameter of the wheel in mm (e.g., 100mm).
     - motorRatedRPM: Vendor-provided RPM of motor (after gearbox).
       Set 0 if unknown, library will attempt to auto-calc.
     - invertDirection: Set true if gearbox or wiring inverts rotation.
     - activeHigh: true if encoder outputs HIGH for active state (standard),
       false if encoder is active-low (switch or hall-effect type).
  ========================================================= */
  encoder.begin(
    2,      // Pin A
    3,      // Pin B
    600,    // pulsesPerRev
    0,      // gearRatio = 0 for auto-calc
    100,    // wheelDiameter_mm
    0,      // motorRatedRPM unknown, auto-calc enabled
    false,  // invertDirection
    true    // activeHigh
  );

  /* ========================================================
     EXAMPLE 2: Using Active-Low Encoder Input
     --------------------------------------------------------
     - Some mechanical switches or hall-effect sensors pull LOW when active.
       Use activeHigh=false to correctly read pulses and direction.
     - Uncomment the following to initialize a second encoder with active-low:
  ========================================================= */
  // encoder.begin(
  //   4,    // Pin A
  //   5,    // Pin B
  //   600,  // pulsesPerRev
  //   0,    // gearRatio = 0 (auto-calc)
  //   100,  // wheelDiameter_mm
  //   0,    // motorRatedRPM unknown
  //   false,// invertDirection
  //   false // activeHigh = false for active-low sensors
  // );
}

void loop() {
  // Read encoder data
  EncoderData data = encoder.read();

  // Print detailed encoder metrics
  Serial.print("Ticks: ");
  Serial.print(data.tickCount);  // Raw pulse count
  Serial.print(" | Shaft RPM: ");
  Serial.print(data.shaftRPM, 2);  // Motor shaft speed
  Serial.print(" | Angle: ");
  Serial.print(data.shaftAngleDeg, 1);  // Motor shaft angle
  Serial.print(" | Output RPM: ");
  Serial.print(data.outputRPM, 2);  // After gearbox
  Serial.print(" | Wheel Speed: ");
  Serial.print(data.wheelSpeed_mps, 2);  // Linear speed (m/s)
  Serial.print(" m/s (");
  Serial.print(data.wheelSpeed_kmph, 2);
  Serial.print(" km/h)");
  Serial.print(" | Dir: ");
  Serial.println(data.directionForward ? "FWD" : "REV");  // Rotation direction

  delay(500);  // Update every 0.5 seconds
}
