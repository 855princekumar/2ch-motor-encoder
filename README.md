# MotorEncoder Library
 Arduino & Raspberry Pi Pico Quadrature Encoder Reader

**Author:** Prince Kumar (TA - Mechatronics)

**Repo:** [GitHub – 2ch-motor-encoder](https://github.com/855princekumar/2ch-motor-encoder)


<img width="240" height="240" alt="image" src="https://github.com/user-attachments/assets/de08b17a-4c5b-4846-aadc-90539c2e628c" />
<img width="180" height="180" alt="image" src="https://github.com/user-attachments/assets/451d2152-7d8c-4508-83e1-c3c2c9d1578e" />
<img width="140" height="140" alt="image" src="https://github.com/user-attachments/assets/d833e1b1-6dd0-418a-a417-0a5415be735e" />
<img width="240" height="240" alt="image" src="https://github.com/user-attachments/assets/2e19befa-5582-4748-9ea6-a30116b61c3f" />
<img width="180" height="180" alt="image" src="https://github.com/user-attachments/assets/bf3ab679-7bb5-46af-bd12-64e0de0eeb9b" />

##  Features

* Read direction (FWD/REV)
* Get shaft RPM & shaft angle
* Compute output RPM after gearbox
* Calculate wheel speed in m/s and km/h
* Auto-detect gear ratio if motor-rated RPM is given
* Supports active-high & active-low encoders

<img width="1592" height="626" alt="image" src="https://github.com/user-attachments/assets/83ad07f6-7509-4dcd-99a6-6a5c6ac87c70" />

### Works with the following encoder types:

| Encoder Type                 | Signal Type               | Recommended Placement    | Notes                                                    |
| ---------------------------- | ------------------------- | ------------------------ | -------------------------------------------------------- |
| Mechanical Switch            | Digital (active-high/low) | Near wheel shaft         | Good for low-speed experiments; debounce may be required |
| Optical / Photoelectric Slot | Digital (active-high/low) | Motor shaft or wheel     | Fast response, suitable for robotics projects            |
| Magnetic Hall-Effect         | Digital (active-high/low) | Close to rotating magnet | Durable, works in dusty/dirty environments               |
| Incremental Rotary           | Digital quadrature        | Motor shaft              | Provides high resolution angle and speed                 |

##  Quick Start

1. Connect encoder pins:

   * Channel A → GPIO2
   * Channel B → GPIO3
2. Install library: download ZIP → Arduino IDE → Sketch > Include Library > Add .ZIP Library.
3. Load example: File > Examples > MotorEncoder > BasicUsage
4. Open Serial Monitor at 115200 baud.

##  Usage Example

```cpp
#include <MotorEncoder.h>

MotorEncoder encoder;

void setup() {
  Serial.begin(115200);
  encoder.begin(2, 3, 600, 0, 100.0, 300, false, true);
}

void loop() {
  EncoderData data = encoder.read();
  Serial.println(data.shaftRPM);
}
```

##  Parameters

* **pulsesPerRev:** PPR from datasheet (0 if unknown)
* **gearRatio:** if 0, auto-calculated when motorRatedRPM is given
* **wheelDiameter_mm:** wheel outer diameter
* **motorRatedRPM:** vendor RPM (after gearbox)
* **invertDirection:** true if gearbox inverts motion
* **activeHigh:** true for standard encoders, false for switch-based

##  Output Data (EncoderData struct)

| Field            | Unit  | Description            |
| ---------------- | ----- | ---------------------- |
| tickCount        | ticks | Raw pulse count        |
| directionForward | bool  | Rotation direction     |
| shaftRPM         | RPM   | Motor shaft speed      |
| shaftAngleDeg    | °     | Shaft angular position |
| outputRPM        | RPM   | Gearbox output speed   |
| wheelSpeed_mps   | m/s   | Linear speed           |
| wheelSpeed_kmph  | km/h  | Linear speed           |
| wheelAngleDeg    | °     | Wheel angular position |

##  Applications

* Robotics
* Differential drive control
* AGVs & line-followers
* Mechatronics labs (teaching tool)

##  References and Further Reading

* [Quadrature Encoder Basics – Video 1 (YouTube)](https://www.youtube.com/watch?v=woCLkFvYCb0&t=9s)
* [Type of Encoder as Absolute or Incremental – Video 2 (YouTube)](https://www.youtube.com/watch?v=-Qk--Sjgq78)
* [Arduino Official Interrupt Reference](https://docs.arduino.cc/language-reference/en/functions/external-interrupts/attachInterrupt/)
* [Quadrature Encoder Wikipedia Article](https://en.wikipedia.org/wiki/Rotary_encoder#Incremental_rotary_encoder)
* [Pico Arduino Core Documentation](https://arduino-pico.readthedocs.io/en/latest/)
* [PJRC Encoder Library (for comparison)](https://www.pjrc.com/teensy/td_libs_Encoder.html)

These links give background on how encoders work, how interrupts are handled on Arduino-style boards, and how the common Encoder library implements similar functionality.

##  License

MIT License – Free to use for projects, teaching, and research.
