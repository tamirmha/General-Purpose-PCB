#include "example_config.h"
#ifdef EX_3A_MOTOR_FIXED

#include "main.h"

extern TIM_HandleTypeDef htim16;



void Run_Example(void) {
    
        HAL_TIM_PWM_Start(&htim16, TIM_CHANNEL_1);
        __HAL_TIM_SET_COMPARE(&htim16, TIM_CHANNEL_1, 500);
    
    while(1) {
        
        if (HAL_GPIO_ReadPin(MOTOR_CW_GPIO_Port, MOTOR_CW_Pin) == GPIO_PIN_SET) {
            HAL_GPIO_WritePin(MOTOR_DIR_GPIO_Port, MOTOR_DIR_Pin, GPIO_PIN_SET);
            __HAL_TIM_SET_COMPARE(&htim16, TIM_CHANNEL_1, 500); // 50% Speed
        } else if (HAL_GPIO_ReadPin(MOTOR_CCW_GPIO_Port, MOTOR_CCW_Pin) == GPIO_PIN_SET) {
            HAL_GPIO_WritePin(MOTOR_DIR_GPIO_Port, MOTOR_DIR_Pin, GPIO_PIN_RESET);
            __HAL_TIM_SET_COMPARE(&htim16, TIM_CHANNEL_1, 500); // 50% Speed
        } else {
            __HAL_TIM_SET_COMPARE(&htim16, TIM_CHANNEL_1, 0);   // Stop
        }
        HAL_Delay(50);
    }
}

#endif // EX_3A_MOTOR_FIXED
