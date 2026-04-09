# 4a. Servo Motor: Edge Control via Buttons

### 1) What to connect
* Servo to SERVO header.
* Use MOTOR_CW / MOTOR_CCW buttons.

### 2) What the code does
Generates 50Hz PWM on SERVO_SIG (PA15). CW moves servo to 180 deg (2ms pulse), CCW to 0 deg (1ms pulse).