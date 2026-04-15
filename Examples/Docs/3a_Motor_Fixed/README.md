# 3a. DC Motor: Fixed Speed & Direction Control

### 1) What to connect
* **Inputs:** Connect two physical push buttons to the `MOTOR_CW` and `MOTOR_CCW` terminals. 
* **Output:** Connect your 12V DC motor to the motor output terminals on the board.

### 2) What the code does
This example introduces basic H-bridge motor control. It actively reads the two directional push buttons:
* If the `MOTOR_CW` button is pressed, the code drives the `MOTOR_DIR` pin LOW and sets the PWM signal to roughly 50% power (`32767`).
* If the `MOTOR_CCW` button is pressed, it flips the `MOTOR_DIR` pin HIGH (reversing the polarity to the motor) and again outputs 50% power.
* If neither button is pressed, it safely drops the PWM duty cycle to `0` to stop the motor completely.

### 3) CubeMX Configuration
* **GPIO Inputs:**
  * `MOTOR_CW` & `MOTOR_CCW`: Configured as `GPIO_Input`. *(Note: Because the code checks for `GPIO_PIN_RESET`, enable `Pull-up` resistors for these pins if your buttons pull to Ground).*
* **GPIO Output:**
  * `MOTOR_DIR`: Configured as `GPIO_Output` to control the H-bridge direction logic.
* **Timers -> TIM16 (Motor PWM):**
  * *Mode:* Channel 1 -> `PWM Generation CH1`.
  * *Parameter Settings:* Prescaler `0`, Counter Period `65535`.

### 4) How to run and test
1. Flash the code to your STM32.
2. Press and hold the `MOTOR_CW` button. The motor will spin clockwise at half speed.
3. Release the button, and the motor will stop.
4. Press and hold the `MOTOR_CCW` button. The motor will smoothly spin in the exact opposite direction at the same half-speed rate.