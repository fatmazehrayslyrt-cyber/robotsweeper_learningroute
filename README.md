# robotsweeper_learningroute
STM32-based robot vacuum cleaner prototype with line tracking and route learning capabilities



INTRODUCTION

This project aims to design a smart embedded system that can learn its own route and re-execute it. The robot to be designed uses sensors to track a line while simultaneously recording the directions it has traversed and can then repeat the route without using sensors. This project will be implemented using the STM32F103C8 microcontroller and combines real-time sensing, motor control, data recording, and memory execution on a single platform. The robot to be designed first stores directional information (right, left, straight) in memory as it moves along the line, using sensors. In a second phase, it disables the sensors and repeats the learned route. Thus, this project provides a practical demonstration of the concept of memory-based embedded control.

Purpose of the Project

The goal of this project is to enable an STM32-based line-following robot to both learn and repeat the path. The robot memorizes directional information as it follows the line using IR sensors (PA0–PA4) and stores this data in an array structure within the STM32's memory. Speed and direction control of the motors is achieved via the L298N motor driver board using the STM32's PWM and direction pins. A button (PC13) indicates mode switching, and an LED (PA5) indicates active mode. The recorded route is also transferred to the computer via a UART (PA9–PA10).

System Architecture and Connection Diagram

It is based on the microcontroller STM32F103C8, and includes an L298N motor driver, five IR sensors, a button, and an LED.The GND line is common for all modules. The power source is a 4x3.7V Li-ion battery pack.The L298N motor driver module supplies 12V to both motors and provides a 5V regulated output to power the STM32 and sensors. In Record mode, sensor data is read and stored in memory, while in the Replay mode, the motors repeat the same motion sequence using this recorded sequence.

Expected Results

In Record mode, the robot should be able to trace the line properly while memorizing all its direction movements, such as left, right, and straight lines. When switched to Replay mode, it will switch off the sensors and go through exactly the same route. It will indicate active mode through an LED and send the recorded route data to the terminal screen via UART. This project would implement the fundamental concepts of an embedded system in the real world, including PWM-based motor control, GPIO communication, interrupt management, and memory-based decision algorithms.

![WhatsApp Görsel 2025-11-30 saat 13 22 59_f055d78b](https://github.com/user-attachments/assets/b55a444a-be86-4ca7-b1dd-cb13d7ba8bd3)

| Component                | Function                                       | STM32F103C8 Pin(s)                                                           |
| ------------------------ | ---------------------------------------------- | ---------------------------------------------------------------------------- |
| **STM32F103C8**          | Main MCU: PWM, ADC, UART, GPIO control         | PA0, PA1, PA4, PA5, PA6, PA2, PA3, PA8, PA9, PB0, PB1, PB5, PB10, PB11, PC13 |
| **L298N**                | Dual H-bridge motor driver (left/right motors) | PA8, PA9, PB0, PB1, PB10, PB11                                               |
| **IR Sensor Array (5×)** | Line detection, analog outputs                 | PA0, PA1, PA4, PA5, PA6                                                      |
| **HC-05 Bluetooth**      | Wireless UART communication                    | PA2, PA3                                                                     |
| **Button**               | Mode switch (Record/Replay)                    | PC13                                                                         |
| **LED**                  | Status indication                              | PB5                                                                          |


