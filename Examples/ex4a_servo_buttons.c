#include "example_config.h"
#ifdef EX_4A_SERVO_BUTTONS

#include "main.h"

extern TIM_HandleTypeDef htim2;



void Run_Example(void) {
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
    
    while(1) {
        
        if (HAL_GPIO_ReadPin(MOTOR_CW_GPIO_Port, MOTOR_CW_Pin) == GPIO_PIN_SET) {
            __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, 2000);
        } else if (HAL_GPIO_ReadPin(MOTOR_CCW_GPIO_Port, MOTOR_CCW_Pin) == GPIO_PIN_SET) {
            __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, 1000);
        } else {
            __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, 1500);
        }
        HAL_Delay(20);
    }
}

#endif // EX_4A_SERVO_BUTTONS
