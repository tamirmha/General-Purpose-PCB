# 11. Digital Sensor Interface (NPN / PNP)

### 1) What to connect
* **Power**: Sensor's Brown wire to `+VIN`, Blue wire to `GND`.
* **Signal**: Sensor's Black wire to the `SIG` pin.
* **Jumpers (CRITICAL)**: Move BOTH jumpers (J8 and J9) to the NPN side or BOTH to the PNP side to match your sensor type.

### 2) What the code does
Mirrors the sensor state to the User LED and implements basic Edge Detection for counting objects passing the sensor.