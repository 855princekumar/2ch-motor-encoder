/*
  encoder_reader.h  -  Header-only Quadrature Encoder Reader
  -----------------------------------------------------------
  - Drop this file next to your .ino
  - Call initEncoder(pinA, pinB, pulsesPerRev)
  - Call getEncoderData() to read results
*/

#ifndef ENCODER_READER_H
#define ENCODER_READER_H

struct EncoderData {
  long count;
  bool directionForward;
  float revPerSec;
  float angle;
  unsigned long interval;
};

// Internal vars
static byte _pinA, _pinB;
static int _pulsesPerRev;
static volatile long _encoderCount = 0;
static volatile bool _dirForward = true;
static volatile unsigned long _lastPulseTime = 0;
static volatile unsigned long _pulseInterval = 0;

void _handleEncoderA() {
  unsigned long now = micros();
  _pulseInterval = now - _lastPulseTime;
  _lastPulseTime = now;

  bool A = digitalRead(_pinA);
  bool B = digitalRead(_pinB);

  if (A == B) {
    _encoderCount++;
    _dirForward = true;
  } else {
    _encoderCount--;
    _dirForward = false;
  }
}

void initEncoder(byte pinA, byte pinB, int pulsesPerRev) {
  _pinA = pinA;
  _pinB = pinB;
  _pulsesPerRev = pulsesPerRev;

  pinMode(_pinA, INPUT_PULLUP);
  pinMode(_pinB, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(_pinA), _handleEncoderA, CHANGE);
}

EncoderData getEncoderData() {
  EncoderData data;
  noInterrupts();
  data.count = _encoderCount;
  data.directionForward = _dirForward;
  data.interval = _pulseInterval;
  interrupts();

  float revPerSec = 0.0;
  if (data.interval > 0) {
    float pulsesPerSec = 1000000.0 / data.interval;
    revPerSec = pulsesPerSec / _pulsesPerRev;
  }
  data.revPerSec = revPerSec;
  data.angle = (data.count % _pulsesPerRev) * (360.0 / _pulsesPerRev);
  return data;
}

#endif
