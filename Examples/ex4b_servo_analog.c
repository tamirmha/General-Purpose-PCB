#include "example_config.h"
#ifdef EX_4B_SERVO_ANALOG

#include "main.h"

extern TIM_HandleTypeDef htim2;
extern ADC_HandleTypeDef hadc1;

uint32_t adc_value = 0;
uint32_t servo_pulse = 0;

void Run_Example(void) {
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
    
    while(1) {
        
        HAL_ADC_Start(&hadc1);
        if (HAL_ADC_PollForConversion(&hadc1, 10) == HAL_OK)	adc_value = HAL_ADC_GetValue(&hadc1);
        HAL_ADC_Stop(&hadc1);
        servo_pulse = ((adc_value * 1000) / 4095) + 1000;
        __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, servo_pulse);
        HAL_Delay(15);
    }
}

#endif // EX_4B_SERVO_ANALOG
