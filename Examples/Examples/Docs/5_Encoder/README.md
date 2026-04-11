# 5 Quadrature Encoder Reading with RPM & UART Output

### 1) What to connect
* **Encoder Power:** Connect the motor encoder's VCC to the board's 3.3V, and GND to GND.
* **Encoder Signals:** Connect Encoder Channel A to `PA8` and Encoder Channel B to `PA9`.
* **Communication:** Connect the ST-LINK V3 via USB to use the Virtual COM Port (PB6/PB7).

### 2) What the code does
Tracks the infinite rotation of a quadrature encoder using non-blocking stopwatch code (`HAL_GetTick()`). It uses physical hardware parameters to calculate the exact physical position (`rounds` and `degrees`) and live speed (`RPM`). It handles 16-bit hardware timer rollovers automatically and streams all data over UART every 100ms.

### 3) CubeMX Configuration
* **Connectivity -> USART1:**
  * *Mode:* Asynchronous, 115200 Baud.
  * *Advanced:* `TX/RX pins swap` Enabled (fixes physical board schematic).
* **Timers -> TIM1:** * *Mode:* Combined Channels -> `Encoder Mode TI1 and TI2`
  * *Parameter Settings:* Prescaler `0`, Counter Period `65535`, Channel 1 & 2 Input Filters `15`.
  * *GPIO Settings:* Pins `PA8` and `PA9` must be set to `Pull-up`.

### 4) How to run and test
1. Click the **Debug/Run** button to flash the code.
2. Open your Serial Monitor.
3. Connect to the ST-Link COM port at **115200 Baud**.
4. Spin the wheel by hand. You will see the angle update. If you spin it continuously, the RPM value will track your speed!