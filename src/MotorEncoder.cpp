#include "MotorEncoder.h"

MotorEncoder* MotorEncoder::instance = nullptr;

MotorEncoder::MotorEncoder() : encoderCount(0), directionForward(true),
    _pulsesPerRev(0), _gearRatio(0), _wheelDiameter_mm(0), _motorRatedRPM(0),
    _invertDirection(false), _activeHigh(true), _lastTime(0), _lastCount(0) {}

void MotorEncoder::begin(uint8_t pinA, uint8_t pinB, int pulsesPerRev,
             float gearRatio, float wheelDiameter_mm, float motorRatedRPM,
             bool invertDirection, bool activeHigh) {

  _pinA = pinA; _pinB = pinB;
  _pulsesPerRev = pulsesPerRev;
  _gearRatio = gearRatio;
  _wheelDiameter_mm = wheelDiameter_mm;
  _motorRatedRPM = motorRatedRPM;
  _invertDirection = invertDirection;
  _activeHigh = activeHigh;

  pinMode(_pinA, INPUT);
  pinMode(_pinB, INPUT);

  instance = this;
  attachInterrupt(digitalPinToInterrupt(_pinA), handleISR_A, RISING);

  _lastTime = millis();
}

void MotorEncoder::handleISR_A() {
  if (!instance) return;
  bool b = digitalRead(instance->_pinB);

  if (instance->_activeHigh) {
    if (b) { instance->encoderCount++; instance->directionForward = true; }
    else   { instance->encoderCount--; instance->directionForward = false; }
  } else {
    if (!b) { instance->encoderCount++; instance->directionForward = true; }
    else    { instance->encoderCount--; instance->directionForward = false; }
  }
}

EncoderData MotorEncoder::read() {
  EncoderData data;

  unsigned long now = millis();
  unsigned long dt = now - _lastTime;
  long currentCount = encoderCount;
  long deltaCount = currentCount - _lastCount;

  float shaftRev = (float)currentCount / (_pulsesPerRev > 0 ? _pulsesPerRev : 1);
  float deltaRev = (float)deltaCount / (_pulsesPerRev > 0 ? _pulsesPerRev : 1);
  float shaftRevPerSec = (deltaRev) / (dt / 1000.0 + 1e-6);

  bool dir = _invertDirection ? !directionForward : directionForward;
  float shaftRPM = shaftRevPerSec * 60.0;
  float shaftAngle = fmod(shaftRev, 1.0) * 360.0;

  if (_gearRatio == 0) {
    if (_motorRatedRPM > 0 && shaftRPM > 0) {
      _gearRatio = shaftRPM / _motorRatedRPM;
    } else {
      _gearRatio = 1.0;
    }
  }

  float outputRPM = shaftRPM / _gearRatio;

  float wheelSpeed = NAN, wheelAngle = NAN;
  if (_wheelDiameter_mm > 0) {
    float wheelCirc = PI * (_wheelDiameter_mm / 1000.0);
    wheelSpeed = (outputRPM / 60.0) * wheelCirc;
    wheelAngle = fmod(shaftRev / _gearRatio, 1.0) * 360.0;
  }

  data.tickCount = currentCount;
  data.directionForward = dir;
  data.shaftRPM = shaftRPM;
  data.shaftAngleDeg = shaftAngle;
  data.outputRPM = outputRPM;
  data.wheelSpeed_mps = wheelSpeed;
  data.wheelSpeed_kmph = wheelSpeed * 3.6;
  data.wheelAngleDeg = wheelAngle;

  _lastTime = now;
  _lastCount = currentCount;

  return data;
}
