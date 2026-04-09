# 3b. DC Motor: Analog PWM & Button Direction

### 1) What to connect
* Potentiometer to Analog Input.
* Use MOTOR_CW / MOTOR_CCW buttons.

### 2) What the code does
Reads analog voltage (0-4095), maps it to PWM (0-1000), and applies it based on direction buttons.