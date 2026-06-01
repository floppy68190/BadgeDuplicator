# BadgeDuplicator

Arduino-based RFID badge reader and writer using the MFRC522 module.

## Overview

BadgeForge is an Arduino project that allows reading the contents of a MIFARE Classic RFID badge and writing the captured data onto another compatible badge.

The project supports two operating modes:

* **Read Mode**: captures and stores the content of a badge.
* **Write Mode**: writes the previously captured data to another badge.

A push button is used to switch between modes, while LEDs and a buzzer provide visual and audio feedback.

## Features

* Read all sectors of a MIFARE Classic card.
* Store card data in Arduino memory.
* Write stored data to another RFID card.
* Audio feedback through a buzzer.
* Visual status indicators with LEDs.
* Enable or disable sound notifications with a long button press.

## Hardware Requirements

* Arduino Uno (or compatible board)
* MFRC522 RFID Reader/Writer
* Push Button
* Buzzer
* LEDs
* Jumper wires

## Wiring

| Component        | Arduino Pin |
| ---------------- | ----------- |
| MFRC522 SDA (SS) | 10          |
| MFRC522 RST      | 5           |
| Valid LED        | 7           |
| Error LED        | 9           |
| Buzzer           | 6           |
| Mode LED         | 3           |
| Button           | 2           |

## Libraries

Install the following libraries through the Arduino IDE:

* SPI
* MFRC522

## Operating Modes

### Read Mode

When the mode LED is OFF:

1. Present an RFID badge to the reader.
2. The card data is read sector by sector.
3. Data is stored in memory.
4. A confirmation LED and buzzer indicate success.

### Write Mode

When the mode LED is ON:

1. Present a writable RFID badge.
2. The stored data is written to the card.
3. A confirmation LED and buzzer indicate success.

## Controls

### Short Press

Switch between:

* Read Mode
* Write Mode

### Long Press (2 seconds)

Enable or disable sound notifications.

## Status Indicators

### Success

* Green LED lights up.
* Confirmation tone is played (if sound is enabled).

### Error

* Error LED flashes.
* Authentication or read/write operation failed.

## Technical Details

The project:

* Authenticates each sector using Key A and Key B.
* Uses the default MIFARE key (`FF FF FF FF FF FF`).
* Reads up to 64 blocks of 16 bytes.
* Stores data in RAM before writing.

## Project Structure

```text
.
├── main.ino
├── badge.cpp
├── badge.hpp
└── README.md
```

### main.ino

Manages:

* User interface
* Button handling
* LEDs
* Buzzer
* Mode switching

### badge.cpp / badge.hpp

Implements:

* RFID initialization
* Card authentication
* Block reading
* Block writing

## Disclaimer

This project is intended for educational, testing, and laboratory purposes only.

Only read from and write to RFID badges that you own or are explicitly authorized to use.

The authors assume no responsibility for misuse of this software or hardware.

## Authors

- floppy68190 GitHub: https://github.com/floppy68190
