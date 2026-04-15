# 11. Digital Sensor Input (Proximity / Limit Switch)

### 1) What to connect
* **Input:** Connect a digital sensor (e.g., optical infrared, magnetic hall-effect, or a physical limit switch) to the `DIGITAL_SENS` terminal. Ensure the sensor shares common Ground and Power with the board if it requires an external supply.
* **Output:** The onboard `PCB_LED`.

### 2) What the code does
This example demonstrates how to read a standard industrial digital sensor. The microcontroller polls the sensor's state every 10 milliseconds. 
* If the sensor is triggered and sends a `HIGH` (SET) signal, the onboard LED turns ON.
* If the sensor is idle and sends a `LOW` (RESET) signal, the LED turns OFF. 

**Pro-Tip (Edge Detection):** The code also includes commented-out logic for an `object_counter`. By comparing the `current_state` to the `prev_state`, it detects the exact moment the sensor transitions from LOW to HIGH (a "rising edge"). If uncommented, this allows the STM32 to accurately count objects passing by on a conveyor belt without double-counting them while the sensor is blocked!

### 3) CubeMX Configuration
* **GPIO Input:**
  * `DIGITAL_SENS`: Configured as `GPIO_Input`. 
  * *(Note: If your sensor actively drives the voltage HIGH and LOW, no pull resistor is needed. If your sensor acts like an open switch, enable `Pull-down` or `Pull-up` depending on its default state).*
* **GPIO Output:**
  * `PCB_LED`: Configured as `GPIO_Output`.

### 4) How to run and test
1. Flash the code to your STM32.
2. Trigger your digital sensor (e.g., wave your hand in front of the optical sensor, or press the limit switch).
3. The onboard LED will instantly mirror the state of the sensor. 
4. **Bonus:** Open a Debug session and add `current_state`, `prev_state`, and `object_counter` to your **Live Expressions** tab. Uncomment the counter logic in the code, run it, and watch the STM32 perfectly count how many times you trigger the sensor!