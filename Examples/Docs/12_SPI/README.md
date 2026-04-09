# 12. SPI Communication

### 1) What to connect
* Any SPI peripheral to the SPI header (`+3V3`, `GND`, `SCK`, `MOSI`, `MISO`, `NCS`).

### 2) What the code does
Demonstrates a standard SPI transaction: pulls Chip Select LOW, transmits/receives data via SPI2, and pulls Chip Select HIGH.