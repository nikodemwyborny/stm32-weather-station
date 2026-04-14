# STM32 Weather Station

STM32-based weather station using BME280 sesnor and I2C OLED display.

## Planned Features
- [*] UART communication for debuging
- [*] Temperature mesurment
- [*] Humidity mesurment
- [*] Pressure mesurment
- [] OLED display (I2C)

## Future Ideas
- Integrate FreeRTOS for task-based system architecture

## Status
Work in progress...

## Hardware
- STM32 NUCLEO-F446RE
- BME280 Sensor
- SSD1306 OLED display (128x64)

## Author
- Nikodem Wyborny

## Licenses

This project includes a custom BME280 driver implemented based on the Bosch datasheet and reference algorithms.

This project uses stm32-ssd1306 library:

Copyright (c) 2018 Aleksander Alekseev

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN