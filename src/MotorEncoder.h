/*
  MotorEncoder.h - Arduino Library for Quadrature Encoders
  --------------------------------------------------------
  Supports:
    - Incremental encoders (optical, magnetic, mechanical)
    - Direction detection
    - Shaft RPM & Angle
    - Output RPM after gearbox
    - Wheel speed (m/s, km/h)
    - Auto gear ratio calculation (if not provided)
    - Active High/Low input selection
    - Inverted gear ratio handling

  Author: Prince Kumar
  License: MIT
*/

#ifndef MotorEncoder_h
#define MotorEncoder_h

#include "Arduino.h"

struct EncoderData {
  long tickCount;
  bool directionForward;
  float shaftRPM;
  float shaftAngleDeg;
  float outputRPM;
  float wheelSpeed_mps;
  float wheelSpeed_kmph;
  float wheelAngleDeg;
};

class MotorEncoder {
public:
  MotorEncoder();
  void begin(uint8_t pinA, uint8_t pinB, int pulsesPerRev = 0, float gearRatio = 0,
             float wheelDiameter_mm = 0, float motorRatedRPM = 0, 
             bool invertDirection = false, bool activeHigh = true);

  EncoderData read();

private:
  static void handleISR_A();
  static MotorEncoder* instance;

  volatile long encoderCount;
  volatile bool directionForward;

  uint8_t _pinA, _pinB;
  int _pulsesPerRev;
  float _gearRatio;
  float _wheelDiameter_mm;
  float _motorRatedRPM;
  bool _invertDirection;
  bool _activeHigh;

  unsigned long _lastTime;
  long _lastCount;
};

#endif
