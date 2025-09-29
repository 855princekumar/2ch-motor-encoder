/*
Prepared BY: Prince Kumar (TA-Mechatronics)
GitHub: https://github.com/855princekumar/2ch-motor-encoder
--------------------------------------------------------------------------
Basic 2-Channel (Quadrature) Encoder Reader for Raspberry Pi Pico (Arduino)
--------------------------------------------------------------------------
Logic:
- Uses Channel A edge as the main trigger.
- Reads Channel B to determine rotation direction.
- Measures time gap between consecutive pulses on Channel A (micros()).
- From pulse gap we calculate:
    * Direction (forward/reverse)
    * Speed (rev/sec)
    * Angle (degrees per pulse count)

This is a simplified, library-free approach suitable for teaching.
It can be wrapped as a function or small library later.
*/

const byte encoderPinA = 2; // GPIO2
const byte encoderPinB = 3; // GPIO3

volatile long encoderCount = 0;        // total pulses counted
volatile bool directionForward = true; // true = forward, false = reverse

volatile unsigned long lastPulseTime = 0;  // µs at previous pulse
volatile unsigned long pulseInterval = 0;  // µs between pulses

const int pulsesPerRevolution = 600; // set to your encoder PPR

void setup() {
  Serial.begin(115200);
  pinMode(encoderPinA, INPUT_PULLUP);
  pinMode(encoderPinB, INPUT_PULLUP);

  // attach interrupts on Channel A edges
  attachInterrupt(digitalPinToInterrupt(encoderPinA), handleEncoderA, CHANGE);
}

void loop() {
  // copy volatile variables safely
  noInterrupts();
  long count = encoderCount;
  bool dir = directionForward;
  unsigned long interval = pulseInterval;
  interrupts();

  // calculate speed (rev/sec)
  float revPerSec = 0.0;
  if (interval > 0) {
    float pulsesPerSec = 1000000.0 / interval;
    revPerSec = pulsesPerSec / pulsesPerRevolution;
  }

  // calculate angular position
  float degrees = (count % pulsesPerRevolution) * (360.0 / pulsesPerRevolution);

  // print data
  Serial.print("Count: "); Serial.print(count);
  Serial.print(" | Dir: "); Serial.print(dir ? "FWD" : "REV");
  Serial.print(" | Rev/s: "); Serial.print(revPerSec, 2);
  Serial.print(" | Angle: "); Serial.print(degrees, 1);
  Serial.print(" deg");
  Serial.print(" | Interval: "); Serial.print(interval); Serial.println(" us");

  delay(200);
}

void handleEncoderA() {
  // triggered on any edge of Channel A
  unsigned long now = micros();
  pulseInterval = now - lastPulseTime;
  lastPulseTime = now;

  // determine direction from Channel B
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
