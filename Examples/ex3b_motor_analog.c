#include "example_config.h"
#ifdef EX_3B_MOTOR_ANALOG

#include "main.h"
#include <stdio.h>
#include <string.h>

extern TIM_HandleTypeDef htim16;
extern ADC_HandleTypeDef hadc1;
extern UART_HandleTypeDef huart1;  // Brought in for Serial Printing!

uint32_t adc_value = 0;
uint32_t pwm_speed = 0;
char serial_buffer[100];           // Buffer to hold our text

uint32_t Read_ADC_Channel(uint32_t channel) {
    ADC_ChannelConfTypeDef sConfig = {0};

    // Configure the internal switch to point to the requested channel
    sConfig.Channel = channel;
    sConfig.Rank = ADC_REGULAR_RANK_1;
    sConfig.SamplingTime = ADC_SAMPLINGTIME_COMMON_1;
    HAL_ADC_ConfigChannel(&hadc1, &sConfig);

    // Give the hardware a tiny moment to stabilize
    for (volatile int i = 0; i < 100; i++) {}

    // --- SOFTWARE FILTERING (AVERAGING) ---
    uint32_t total_adc_value = 0;
    const int NUM_SAMPLES = 16; // Take 16 rapid-fire readings

    for (int i = 0; i < NUM_SAMPLES; i++) {
        HAL_ADC_Start(&hadc1);
        HAL_ADC_PollForConversion(&hadc1, 10);
        total_adc_value += HAL_ADC_GetValue(&hadc1);
        HAL_ADC_Stop(&hadc1);
    }

    // Divide the total by the number of samples to get the smooth average
    return (total_adc_value / NUM_SAMPLES);
}

void Run_Example(void) {
    HAL_TIM_PWM_Start(&htim16, TIM_CHANNEL_1);
    
    // Print a startup message
    char *startup_msg = "Motor PWM Debug Started...\r\n";
    HAL_UART_Transmit(&huart1, (uint8_t*)startup_msg, strlen(startup_msg), HAL_MAX_DELAY);

    while(1) {
        
        // 1. Read the External Potentiometer on Channel 0
        adc_value = Read_ADC_Channel(ADC_CHANNEL_0);
		// Step A: Apply boundaries (Dead zones for the top and bottom)
		if (adc_value < 130)  adc_value = 130;  // Force bottom noise to 130
		if (adc_value > 2050) adc_value = 2050; // Cap the top near the max

		// Step B: Shift the bottom down to absolute zero
		uint32_t active_adc = adc_value - 130;

		// Step C: Scale the remaining range (2050 - 130 = 1920) to full PWM (65535)
		pwm_speed = active_adc; // (active_adc * 65535) / 1920;
//        // 2. Scale the 0-4095 ADC range perfectly into the 0-65535 PWM range
//        pwm_speed = (adc_value * 65535) / 4095;

        // 3. --- SERIAL DEBUG PRINT ---
        sprintf(serial_buffer, "Raw ADC: %lu | Desired PWM: %lu\r\n", adc_value, pwm_speed);
        HAL_UART_Transmit(&huart1, (uint8_t*)serial_buffer, strlen(serial_buffer), HAL_MAX_DELAY);

        // 4. Set Direction and Speed
        if (HAL_GPIO_ReadPin(MOTOR_CW_GPIO_Port, MOTOR_CW_Pin) == GPIO_PIN_RESET)
        {
            HAL_GPIO_WritePin(MOTOR_DIR_GPIO_Port, MOTOR_DIR_Pin, GPIO_PIN_RESET);
            __HAL_TIM_SET_COMPARE(&htim16, TIM_CHANNEL_1, pwm_speed);
        }
        else if (HAL_GPIO_ReadPin(MOTOR_CCW_GPIO_Port, MOTOR_CCW_Pin) == GPIO_PIN_RESET)
        {
            HAL_GPIO_WritePin(MOTOR_DIR_GPIO_Port, MOTOR_DIR_Pin, GPIO_PIN_SET);
            __HAL_TIM_SET_COMPARE(&htim16, TIM_CHANNEL_1, pwm_speed);
        }
        else {
            __HAL_TIM_SET_COMPARE(&htim16, TIM_CHANNEL_1, 0);   // Stop motor when no buttons are pressed
        }

        // Slowed down to 100ms just for easier reading on the monitor!
        HAL_Delay(100);
    }
}

#endif // EX_3B_MOTOR_ANALOG
