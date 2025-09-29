# Basic 2-Channel Motor Encoder (Raspberry Pi Pico / Arduino)

Prepared by: Prince Kumar (TA-Mechatronics)  
GitHub: [https://github.com/855princekumar/2ch-motor-encoder](https://github.com/855princekumar/2ch-motor-encoder)

## Overview

This is a minimal, library-free implementation of a 2-channel (quadrature) motor encoder reader for Raspberry Pi Pico using the Arduino framework.

The code uses direct interrupts and `micros()` to measure time between pulses on Channel A, while using Channel B to determine direction. From these two signals it calculates:

- Rotation direction (forward/reverse)
- Speed (revolutions per second)
- Angular position (degrees per pulse count)

## Why not use Encoder.h?

- No external library dependency: Students can see the raw logic.
- Lower memory footprint: only simple interrupt handlers and math.
- Easier to adapt into a function or DAQ (data acquisition) routine.
- Transparent teaching example: directly shows how timing and direction decoding works.

## How to Use

1. Wire your quadrature encoder Channel A to GPIO2 and Channel B to GPIO3 (change pins in code if needed).
2. Set `pulsesPerRevolution` to your encoder’s specification.
3. Upload the sketch to Raspberry Pi Pico (Arduino core).
4. Open Serial Monitor at 115200 baud to view count, direction, speed and angle.

## License

Feel free to fork and modify for educational or project purposes.
