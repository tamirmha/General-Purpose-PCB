# Example 3D: Closed-Loop Motor Control (PID)

## Overview
This example demonstrates how to create a "Closed-Loop" Proportional (P) controller to regulate the speed of a DC motor. Unlike open-loop control (which blindly sends power), this code actively measures the motor's real speed using a quadrature encoder and adjusts the power (PWM) to maintain the target speed regardless of friction or load.

## Hardware Requirements
* **Motor:** JGB37-520 (12V, 330 RPM)
* **Encoder:** Magnetic Quadrature Encoder (11 PPR base, 1320 CPR final after 30:1 gearbox and 4x hardware timer multiplier)
* **Input:** Onboard Potentiometer to set the target RPM (0 to 300 RPM)
* **Output:** H-Bridge Motor Driver connected to `TIM16_CH1`

## How It Works
1.  **Target RPM:** The ADC reads the potentiometer (0-4095) and mathematically scales it to a requested speed of 0 to 300 RPM.
2.  **Current RPM:** The STM32 hardware Timer 1 (`TIM1`) reads the encoder A/B pulses. Every 50 milliseconds, the code calculates how many ticks occurred and converts that to the actual physical RPM of the output shaft.
3.  **The Feedback Loop (P-Controller):** The code subtracts the *Actual RPM* from the *Target RPM* to find the "Error". It multiplies this error by a Tuning Gain (`Kp = 5.0`) and adds it to the current PWM output.
    * If the motor is running too slow (e.g., someone is grabbing the wheel), the error is positive, and the board aggressively pushes more power to compensate.
    * If the motor is running too fast (e.g., going downhill), the error is negative, and power decreases.

## Troubleshooting
* **Runaway Motor (Instantly shoots to 100% speed and won't stop):** Your motor power polarity and encoder reading polarity are fighting each other. The controller is trying to speed up the motor, but the encoder is reading a negative speed, causing it to push even harder in a feedback loop!
    * **The Fix:** Swap the two main power wires (Red/Black) going to the motor, or reverse the `MOTOR_DIR` pin state in the code.
* **Stuttering / Whining:** Ensure your `TIM16` PWM frequency is set to the 20 kHz industry standard in CubeMX (`Prescaler = 0`, `Period = 3199`, `HCLK = 64 MHz`).