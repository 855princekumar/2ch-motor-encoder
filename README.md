# Basic 2-Channel Motor Encoder (Raspberry Pi Pico / Arduino)

Prepared by: Prince Kumar (TA-Mechatronics)  
GitHub: [https://github.com/855princekumar/2ch-motor-encoder](https://github.com/855princekumar/2ch-motor-encoder)

<img width="240" height="240" alt="image" src="https://github.com/user-attachments/assets/2e19befa-5582-4748-9ea6-a30116b61c3f" />
<img width="280" height="280" alt="image" src="https://github.com/user-attachments/assets/bf3ab679-7bb5-46af-bd12-64e0de0eeb9b" />

---

## Overview

This is a minimal, library-free implementation of a 2-channel (quadrature) motor encoder reader for Raspberry Pi Pico using the Arduino framework.

The code uses direct interrupts and `micros()` to measure time between pulses on Channel A, while using Channel B to determine direction. From these two signals, it calculates:

- Rotation direction (forward/reverse)
- Speed (revolutions per second)
- Angular position (degrees per pulse count)

---

## Why not use Encoder.h?

- **No external library dependency** – Students can see the raw logic.
- **Lower memory footprint** – only simple interrupt handlers and math.
- **Easier to adapt** into a function or DAQ (data acquisition) routine.
- **Transparent teaching example** – directly shows how timing and direction decoding works.

---

## How to Use

1. Wire your quadrature encoder Channel A to GPIO2 and Channel B to GPIO3 (change pins in code if needed).
2. Set `pulsesPerRevolution` to your encoder’s specification.
3. Upload the sketch to Raspberry Pi Pico (Arduino core).
4. Open Serial Monitor at 115200 baud to view count, direction, speed and angle.

---

## References and Further Reading

- [Quadrature Encoder Basics – Video 1 (YouTube)](https://www.youtube.com/watch?v=woCLkFvYCb0&t=9s)  
- [Arduino Official Interrupt Reference](https://docs.arduino.cc/language-reference/en/functions/external-interrupts/attachInterrupt/)  
- [Quadrature Encoder Wikipedia Article](https://en.wikipedia.org/wiki/Rotary_encoder#Incremental_rotary_encoder)  
- [Pico Arduino Core Documentation](https://arduino-pico.readthedocs.io/en/latest/)  
- [PJRC Encoder Library (for comparison)](https://www.pjrc.com/teensy/td_libs_Encoder.html)
- [Type of Encoder as Absolute or Incremental](https://www.youtube.com/watch?v=-Qk--Sjgq78)

These links give background on how encoders work, how interrupts are handled on Arduino-style boards, and how the common Encoder library implements similar functionality.

---

## License

Feel free to fork and modify for educational or project purposes.
