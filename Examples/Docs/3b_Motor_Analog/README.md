# 3b. DC Motor: Analog Speed & Direction Control

### 1) What to connect
* **Inputs (Speed):** Connect the middle wiper pin of a Potentiometer to your board's Analog Input (ADC) terminal. Connect the other two outer pins to 3.3V and GND.
* **Inputs (Direction):** Connect two physical push buttons to the `MOTOR_CW` and `MOTOR_CCW` terminals. 
* **Output:** Connect your 12V DC motor to the motor output terminals.

### 2) What the code does
This example marries analog sensor reading with PWM hardware control. It constantly reads the physical position of the potentiometer as a 12-bit value (`0` to `4095`). Because the PWM timer expects a 16-bit value (`0` to `65535`), the code uses a mathematical scaling trick `(adc_value * 65535) / 4095` to perfectly translate the knob's position into a 0% to 100% duty cycle. 
When you hold down one of the directional buttons, the motor will spin in that direction at the exact speed you have dialed in with the potentiometer. Letting go of the buttons safely stops the motor.

### 3) CubeMX Configuration
* **GPIO Inputs:**
  * `MOTOR_CW` & `MOTOR_CCW`: Configured as `GPIO_Input` (Enable `Pull-up` resistors if your buttons pull to Ground).
* **GPIO Output:**
  * `MOTOR_DIR`: Configured as `GPIO_Output` to control the H-bridge direction logic.
* **Analog -> ADC1:**
  * Configure your specific input pin as an `INx Single-ended` channel. Ensure the resolution is set to `12-bit`.
* **Timers -> TIM16 (Motor PWM):**
  * *Mode:* Channel 1 -> `PWM Generation CH1`.
  * *Parameter Settings:* Prescaler `0`, Counter Period `65535`.

### 4) How to run and test
1. Flash the code to your STM32.
2. Turn the potentiometer knob to the halfway position.
3. Press and hold the `MOTOR_CW` button. The motor will spin at 50% speed.
4. **The cool part:** While still holding down the button, twist the potentiometer back and forth. You will hear and see the motor dynamically speed up and slow down in real-time, exactly matching your hand movements!