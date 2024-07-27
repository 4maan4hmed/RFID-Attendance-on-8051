# RFID Attendance System on 8051

## Description

This project implements an RFID-based attendance system using the 8051 microcontroller. It reads RFID tags and displays the corresponding user information on an LCD. The system uses I2C communication for LCD control and serial communication for RFID data reception.

## Features

- Reads RFID tags and processes the data.
- Displays user information on an LCD screen.
- Utilizes I2C for communication with the LCD.
- Provides a simple interface for attendance tracking.

## Hardware Requirements

- 8051 Microcontroller
- RFID Reader
- LCD (with I2C interface)
- External pull-up resistors (if needed)

## Software Requirements

- Keil uVision or any compatible IDE for compiling and flashing the code.

## Pin Configuration

- **SCL**: P0.6 (I2C Clock)
- **SDA**: P0.7 (I2C Data)
- **RX**: Connected to the RFID Reader for serial data reception
- **LCD**: Connected via I2C

## Usage

### Setup

1. Connect the hardware components according to the pin configuration.
2. Open the code in your preferred IDE (e.g., Keil uVision).
3. Compile and upload the code to the 8051 microcontroller.

### Running

1. Power on the system.
2. The LCD will display "Greetings! Please Tap CARD".
3. Tap an RFID card near the reader.
4. The system will display the corresponding user information if the RFID tag matches the pre-defined values.

---
