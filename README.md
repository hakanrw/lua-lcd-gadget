# five-bit-counter

a five bit counter written in C for the RP2040 Raspberry Pi Pico microcontroller.

![five-bit-counter](https://github.com/user-attachments/assets/998074eb-45d7-4de9-9d44-dde7786f20b8)

## required hardware

- Raspberry Pi Pico
- 1x breadboard
- 6x LEDs (5 counter, 1 overflow)
- 2x micro buttons
- 6x 220 ohm resistors
- 2x 10K ohm resistors
- cables

## required software

- CMake
- pico-sdk
- arm-none-eabi cross compiler (gcc preferred, clang works)

## setting up

wire your components like the picture as shown at the top.

if you change your pins, edit `counter.h` appropriately.

## building

```
cmake -B build && cmake --build build
```

## flashing

```
cp ./build/five_bit_counter.uf2 /<the mount place of pico>
```

## license
```
Copyright (c) 2024 Hakan Candar
All rights reserved.

This source code is licensed under the BSD 2-Clause License found in the
LICENSE file in the root directory of this source tree.
```
