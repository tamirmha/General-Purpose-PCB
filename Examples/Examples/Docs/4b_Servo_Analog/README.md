# 4b. Servo Motor: Analog (Potentiometer) Control

### 1) What to connect
* **Input:** Connect the middle wiper pin of a Potentiometer to your board's Analog Input (ADC) terminal. Connect the other two outer pins to 3.3V and GND.
* **Output:** Connect a standard 5V RC Servo motor to the PWM output pin mapped to `TIM2_CH1`. Make sure the servo's Ground is connected to the board's Ground, and it is receiving 5V power.

### 2) What the code does
This code acts as a real-time mechanical linkage. It reads the physical position of the potentiometer knob as a 12-bit value (`0` to `4095`). 
Because the servo requires a precise pulse width between 1000 and 2000 microseconds to sweep its 180-degree range, the code uses a scaling formula: `((adc_value * 1000) / 4095) + 1000`. 
* When the knob is at `0`, the math outputs exactly `1000` (Servo moves all the way left).
* When the knob is at `4095`, the math outputs exactly `2000` (Servo moves all the way right).
The STM32 updates this calculation constantly, meaning the servo will instantly mirror your hand movements.

### 3) CubeMX Configuration
*(Note: This uses the exact same 50Hz Timer math we configured in Example 4a!)*
* **Analog -> ADC1:**
  * Configure your input pin as an `INx Single-ended` channel.
  * *Parameter Settings:* Ensure Resolution is `12-bit`.
* **Timers -> TIM2 (Servo PWM):**
  * *Mode:* Channel 1 -> `PWM Generation CH1`.
  * *Parameter Settings:* * **Prescaler:** `15` *(Divides the 16 MHz clock to 1 tick per microsecond).*
    * **Counter Period:** `19999` *(Creates the strict 20,000 microsecond / 50Hz period).*

### 4) How to run and test
1. Flash the code to your STM32.
2. The servo will snap to whatever position the potentiometer is currently resting at.
3. Slowly twist the potentiometer knob back and forth.
4. The servo arm will smoothly follow your exact movements, behaving exactly like a throttle or steering wheel on an RC car!