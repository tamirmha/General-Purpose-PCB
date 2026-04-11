# General-Purpose STM32G0 Board: Hardware Configuration Guide

This board features several physical jumpers and switches that must be configured correctly depending on the sensors and networks you are connecting. This guide explains what each header does and how to set it.

## 1. Digital Sensor Interface (NPN / PNP Selection)
**Jumpers: J8 and J9**
* **NPN Sensors:** Move BOTH jumpers to the pin labeled `NPN`.
* **PNP Sensors:** Move BOTH jumpers to the pin labeled `PNP`.
*⚠️ Critical: Never mix them. Both must be moved together to ensure the level-shifting circuit operates safely.*

## 2. Analog Input Reference Voltage
**Jumper: "VOLTAGE" Header (Next to the ADC block)**
* **12V Position:** Outputs a regulated 12V to the VCC pin.
* **VIN Position:** Outputs raw input voltage (e.g., 24V) to the VCC pin.

## 3. Communication Termination Resistors (120R)
**Jumpers: J30 (CAN Bus) and unlabeled 120R next to RS485**
* **Jumper ON:** If board is the FIRST or LAST device on the network cable.
* **Jumper OFF:** If board is connected in the MIDDLE of the network.

## 4. DIP Switches (DIP1, DIP2, DIP3)
Hardware toggle switches connected to GPIO inputs (`PB3`, `PF0`, `PF1`). Used for hardware addressing (I2C/RS485 IDs) or runtime mode selection.

## 5. The User Jumper (J13)
* **Jumper ON:** Connects `PC13` to the `USER LED` (PCB_LED).
* **Jumper OFF:** Disconnects the LED so `PC13` can be used for other hardware without interference.

## 6. Thermistor Calibration Potentiometer
The blue/white trimpot near the `THERM` header. Use a small screwdriver to tune the voltage divider so the STM32 ADC reads the mathematically perfect resistance at a known baseline temperature (e.g., 25°C).
