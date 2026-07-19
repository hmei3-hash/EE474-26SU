# EE 474 — Embedded Systems

University of Washington · ECE · Summer 2026

**Authors:** Hongyi Mei, Kevin Bi

## Overview

Hands-on embedded systems labs using the **ESP32-S3-DevKitC-1**, progressing from bare-metal register manipulation to real-time multitasking with FreeRTOS. All code targets the Arduino/ESP-IDF framework.

## Hardware

- ESP32-S3-DevKitC-1 (dual-core Xtensa LX7 @ 240 MHz)
- I2C LCD (PCF8574T, 16×2)
- LEDs, photoresistor, tactile switch, 220Ω / 10KΩ resistors
- Oscilloscope for timing verification

## Labs

### Lab 2 — Hardware Manipulation & Timers
Direct register-level control without Arduino abstractions.
- **GPIO via registers:** `GPIO_ENABLE_REG` / `GPIO_OUT_REG` with bitwise read-modify-write
- **Performance benchmarking:** `digitalWrite()` vs direct register access (1000-iteration timing comparison)
- **Hardware timers:** `TIMG_T0CONFIG_REG`, prescaler configuration, latch-before-read pattern (`TIMG_T0UPDATE_REG`)
- **PWM / LEDC:** Photoresistor-driven LED brightness control; ambient light-triggered frequency sequence

### Lab 3 — Serial Communication, Scheduling & ISRs
I2C communication, task scheduling fundamentals, and interrupt-driven design.
- **I2C / LCD:** Wire library with 4-bit nibble mode; manual command/data transmission via PCF8574T control bits
- **Non-preemptive scheduling:** Priority-based TCB scheduler with function pointers and rotating priorities
- **Interrupts:** External (button via `attachInterrupt`), timer-based counter, BLE callback (`LightBlue` app)

### Lab 4 — Preemptive Scheduling & Parallel Computing
FreeRTOS on the ESP32 dual-core architecture.
- **SRTF scheduling:** Simulated Shortest Remaining Time First via `vTaskSuspend()` / `vTaskResume()` with a higher-priority scheduler task
- **Dual-core execution:** Tasks pinned to Core 0 (sensing, display) and Core 1 (anomaly detection, background computation)
- **Synchronization:** Binary semaphore for shared light-level data between producer/consumer tasks
- **Anomaly detection:** SMA-based threshold monitoring with LED alarm; concurrent prime number computation

## Key Concepts Covered

| Topic | Details |
|-------|---------|
| Register access | Volatile pointers, GPIO matrix (`SIG_GPIO_OUT_IDX`), timer latch registers |
| Timing | Hardware Timer Group 0, prescaler math (80 MHz APB_CLK), `micros()` benchmarking |
| Communication | I2C (Wire), UART (Serial), BLE GATT |
| Scheduling | Non-preemptive priority (TCB array), preemptive SRTF (FreeRTOS suspend/resume) |
| RTOS | `xTaskCreatePinnedToCore`, binary semaphores, `vTaskDelay`, dual-core task pinning |
| Peripherals | LEDC PWM, ADC (`analogRead`), photoresistor voltage divider |

## Build & Flash

1. Install [Arduino IDE](https://www.arduino.cc/en/software) with ESP32 board support (v3.x+)
2. Select board: **ESP32S3 Dev Module**
3. Open the `.ino` file for the target lab part
4. Upload at 115200 baud

## File Structure

```
.
├── Lab2/
│   ├── Lab2_GPIO_Register.ino        # Part I: register-level LED blink
│   ├── Lab2_DigitalWrite_Measure.ino # Part I: digitalWrite timing
│   ├── Lab2_Register_Measure.ino     # Part I: register access timing
│   ├── Lab2_Hardware_Timer.ino       # Part II: timer-driven LED
│   ├── Lab2_Photoresistor_PWM.ino    # Part III: light-adaptive brightness
│   └── Lab2_Light_Frequency.ino      # Part IV: threshold frequency sequence
├── Lab3/
│   ├── Lab3_I2C_LCD.ino              # Part I: Wire library LCD display
│   ├── Lab3_Priority_Scheduler.ino   # Part II: TCB priority scheduling
│   └── Lab3_Interrupts_BLE.ino       # Part III: ISRs + BLE
├── Lab4/
│   ├── Lab4_SRTF.ino                 # Part I: FreeRTOS SRTF simulation
│   └── Lab4_DualCore_Sensor.ino      # Part II: dual-core light monitoring
└── README.md
```

## Code Style

All files follow a consistent documentation template:
- File header block (Filename, Author, Date, Description)
- `#define` macros replacing magic numbers
- Section dividers for logical grouping
- Inline comments explaining register bit-field operations
- Lab 4: Doxygen-formatted documentation

## License

Academic coursework — University of Washington EE 474.
