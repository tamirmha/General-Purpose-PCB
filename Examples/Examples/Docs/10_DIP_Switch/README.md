# 10. DIP Switch Input & Binary Logic

### 1) What to connect
* **Input:** The 3 onboard DIP switches (`DIP1`, `DIP2`, `DIP3`).
* **Output:** The onboard `PCB_LED`.
* *(Note: No external wiring is required for this example).*

### 2) What the code does
This example demonstrates how to read multiple digital inputs and combine them into a single binary number. It reads the three DIP switches to form a 3-bit value ranging from `0` (all switches OFF) to `7` (all switches ON). 
It then uses this number to dynamically calculate a delay time, changing the blinking speed of the onboard LED. The delay ranges from 100ms (fastest) to 800ms (slowest) depending on the physical switch positions.

### 3) CubeMX Configuration
* **GPIO Inputs:**
  * `DIP1`, `DIP2`, `DIP3`: Configured as `GPIO_Input`. 
  * *(Note: Because the code checks for `GPIO_PIN_SET` (Active High), ensure these pins are configured with a `Pull-down` resistor in CubeMX if your physical board does not have hardware pull-down resistors installed).*
* **GPIO Output:**
  * `PCB_LED`: Configured as `GPIO_Output`.

### 4) How to run and test
1. Flash the code to your STM32.
2. Toggle the three DIP switches into different ON/OFF combinations.
3. Watch the onboard LED. You will see the blink rate speed up and slow down instantly as you change the binary value of the switches!