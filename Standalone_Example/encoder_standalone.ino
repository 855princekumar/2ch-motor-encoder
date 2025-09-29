/*
  Basic 2-Channel (Quadrature) Encoder Reader for Raspberry Pi Pico (Arduino)
  Standalone Example
  -----------------------------------------------------------
  - Uses Channel A edge as trigger.
  - Reads Channel B to determine direction.
  - Measures time gap between pulses on Channel A.
  - Calculates direction, speed and angular position.
*/

const byte encoderPinA = 2; // GPIO2
const byte encoderPinB = 3; // GPIO3

volatile long encoderCount = 0;
volatile bool directionForward = true;

volatile unsigned long lastPulseTime = 0;
volatile unsigned long pulseInterval = 0;

const int pulsesPerRevolution = 600;

void setup() {
  Serial.begin(115200);
  pinMode(encoderPinA, INPUT_PULLUP);
  pinMode(encoderPinB, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(encoderPinA), handleEncoderA, CHANGE);
}

void loop() {
  noInterrupts();
  long count = encoderCount;
  bool dir = directionForward;
  unsigned long interval = pulseInterval;
  interrupts();

  float revPerSec = 0.0;
  if (interval > 0) {
    float pulsesPerSec = 1000000.0 / interval;
    revPerSec = pulsesPerSec / pulsesPerRevolution;
  }

  float degrees = (count % pulsesPerRevolution) * (360.0 / pulsesPerRevolution);

  Serial.print("Count: "); Serial.print(count);
  Serial.print(" | Dir: "); Serial.print(dir ? "FWD" : "REV");
  Serial.print(" | Rev/s: "); Serial.print(revPerSec, 2);
  Serial.print(" | Angle: "); Serial.print(degrees, 1);
  Serial.println(" deg");

  delay(200);
}

void handleEncoderA() {
  unsigned long now = micros();
  pulseInterval = now - lastPulseTime;
  lastPulseTime = now;

  bool A = digitalRead(encoderPinA);
  bool B = digitalRead(encoderPinB);

  if (A == B) {
    encoderCount++;
    directionForward = true;
  } else {
    encoderCount--;
    directionForward = false;
  }
}
