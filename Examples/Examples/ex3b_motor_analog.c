#include "example_config.h"
#ifdef EX_3B_MOTOR_ANALOG

#include "main.h"

extern TIM_HandleTypeDef htim16;
extern ADC_HandleTypeDef hadc1;

uint32_t adc_value = 0;
uint32_t pwm_speed = 0;

void Run_Example(void) {
    HAL_TIM_PWM_Start(&htim16, TIM_CHANNEL_1);
    
    while(1) {
        
        // 1. Read the Potentiometer
        HAL_ADC_Start(&hadc1);
        if (HAL_ADC_PollForConversion(&hadc1, 10) == HAL_OK) {
            adc_value = HAL_ADC_GetValue(&hadc1);
        }
        HAL_ADC_Stop(&hadc1);

		// Scale the 0-1365 ADC range perfectly into the 0-65535 PWM range
		pwm_speed = (adc_value * 65535) / 4095;

        // Set Direction and Speed
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
        else	__HAL_TIM_SET_COMPARE(&htim16, TIM_CHANNEL_1, 0);   // Stop motor when no buttons are pressed

        HAL_Delay(10);
    }
}

#endif // EX_3B_MOTOR_ANALOG
