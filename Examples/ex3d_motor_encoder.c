#include "example_config.h"
#ifdef EX_3D_MOTOR_ENCODER

#include "main.h"

// Bring in the hardware handles from main.c
extern TIM_HandleTypeDef htim16; // Motor PWM
extern TIM_HandleTypeDef htim1;  // Encoder Timer
extern ADC_HandleTypeDef hadc1;  // Potentiometer ADC

// --- MOTOR SPECIFIC SETTINGS ---
// YOU MUST CHANGE THIS TO MATCH YOUR SPECIFIC MOTOR!
// This is the number of encoder pulses per 1 full revolution of the output shaft.
#define ENCODER_CPR 1320.0f

#define MAX_PWM 3199         // Based on your 20kHz CubeMX configuration
#define MAX_RPM 300          // The maximum RPM you want the potentiometer to set

void Run_Example(void) {

    // 1. Start the Hardware Peripherals
    HAL_TIM_PWM_Start(&htim16, TIM_CHANNEL_1);
    HAL_TIM_Encoder_Start(&htim1, TIM_CHANNEL_ALL);

    // Variables for the Encoder and RPM math
    uint16_t last_encoder_count = 0;
    int16_t current_rpm = 0;

    // Variables for the Control Loop
    int32_t target_rpm = 0;
    float Kp = 5.0f;  // Proportional Tuning Gain (Increase if motor is too slow to react)
    int32_t current_pwm = 0;

    // Set initial direction to Clockwise
    HAL_GPIO_WritePin(MOTOR_DIR_GPIO_Port, MOTOR_DIR_Pin, GPIO_PIN_RESET);

    while(1) {

        // --- 1. READ THE POTENTIOMETER (TARGET RPM) ---
        HAL_ADC_Start(&hadc1);
        HAL_ADC_PollForConversion(&hadc1, 10);
        uint32_t adc_val = HAL_ADC_GetValue(&hadc1); // Returns 0 to 4095

        // Map the 12-bit ADC value to a 0-300 RPM scale
        target_rpm = (adc_val * MAX_RPM) / 4095;
        if (target_rpm < 20) target_rpm=0;

        // --- 2. READ THE ENCODER (CURRENT RPM) ---
        uint16_t current_encoder_count = __HAL_TIM_GET_COUNTER(&htim1);

        // Cast to signed 16-bit integer. This perfectly handles the timer
        // rolling over from 65535 back to 0 without breaking the math!
        int16_t delta_ticks = (int16_t)(current_encoder_count - last_encoder_count);
        last_encoder_count = current_encoder_count;

        // Calculate actual RPM based on ticks over the 50ms delay
        // RPM = (Delta Ticks / CPR) * (60 seconds / 0.05 seconds)
        current_rpm = (delta_ticks * 60 * 1000) / (ENCODER_CPR * 50);

        // Ensure RPM is positive for this basic forward-only example
        if (current_rpm < 0) current_rpm = -current_rpm;


        // --- 3. THE "P-CONTROLLER" FEEDBACK LOOP ---
        // Calculate how far off we are from the target speed
        int32_t rpm_error = target_rpm - current_rpm;

        // Adjust the PWM based on the error.
        // If we are too slow (positive error), it adds power.
        // If we are too fast (negative error), it reduces power.
        current_pwm = current_pwm + (rpm_error * Kp);

        // Clamp the PWM safely between 0 and our maximum limit (3199)
        if (current_pwm > MAX_PWM) current_pwm = MAX_PWM;
        if (current_pwm < 0) current_pwm = 0;

        // Send the adjusted speed to the motor driver
        __HAL_TIM_SET_COMPARE(&htim16, TIM_CHANNEL_1, current_pwm);


        // --- 4. LOOP TIMING ---
        // Run this math exactly 20 times a second (every 50ms)
        HAL_Delay(50);
    }
}

#endif // EX_3D_MOTOR_ENCODER
