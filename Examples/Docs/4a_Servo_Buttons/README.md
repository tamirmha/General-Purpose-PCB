# 4a. Servo Motor: Button Control

### 1) What to connect
* **Inputs:** Connect two physical push buttons to the `MOTOR_CW` and `MOTOR_CCW` terminals.
* **Output:** Connect a standard 5V RC Servo motor to the PWM output pin mapped to `TIM2_CH1`. Make sure the servo's Ground is connected to the board's Ground, and it is receiving proper 5V power.

### 2) What the code does
This code controls the exact physical angle of a servo motor using PWM pulse widths. 
* If neither button is pressed, it outputs a 1500-microsecond pulse, moving the servo to its center (90-degree) position.
* If `MOTOR_CCW` is pressed, it outputs a 1000-microsecond pulse, moving the servo to its minimum angle (0 degrees).
* If `MOTOR_CW` is pressed, it outputs a 2000-microsecond pulse, moving the servo to its maximum angle (180 degrees).

### 3) CubeMX Configuration (The 50Hz Secret)
Servos require a strict 50Hz frequency. To achieve this, the timer must be scaled to 1 tick per microsecond.
* **GPIO Inputs:**
  * `MOTOR_CW` & `MOTOR_CCW`: Configured as `GPIO_Input` (Enable `Pull-up` resistors if your buttons pull to Ground).
* **Timers -> TIM2 (Servo PWM):**
  * *Mode:* Channel 1 -> `PWM Generation CH1`.
  * *Parameter Settings:* * **Prescaler:** Set to `(Timer Clock in MHz) - 1`. *(Example: If your clock is 64MHz, set this to 63).*
    * **Counter Period:** `19999` *(This equals 20,000 microseconds, which creates the required 20ms / 50Hz period).*

### 4) How to run and test
1. Flash the code to your STM32.
2. The moment it powers on, the servo should physically snap to its center position.
3. Press and hold the `MOTOR_CCW` button. The servo will snap to the left.
4. Press and hold the `MOTOR_CW` button. The servo will sweep across to the right.
5. Let go of the buttons, and it will automatically return to the center!