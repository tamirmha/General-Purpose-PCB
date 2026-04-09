#include "example_config.h"
#ifdef EX_3C_MOTOR_SERIAL

#include "main.h"

extern TIM_HandleTypeDef htim16;
extern UART_HandleTypeDef huart1;

#include <string.h>
#include <stdlib.h>

char rx_buffer[9] = {0};

void Run_Example(void) {
    HAL_TIM_PWM_Start(&htim16, TIM_CHANNEL_1);
    
    while(1) {
        
        if (HAL_UART_Receive(&huart1, (uint8_t*)rx_buffer, 8, HAL_MAX_DELAY) == HAL_OK) {
            if (strncmp(rx_buffer, "CW:", 3) == 0) {
                HAL_GPIO_WritePin(MOTOR_DIR_GPIO_Port, MOTOR_DIR_Pin, GPIO_PIN_SET);
                uint16_t speed = atoi(&rx_buffer[3]);
                __HAL_TIM_SET_COMPARE(&htim16, TIM_CHANNEL_1, speed);
            } else if (strncmp(rx_buffer, "CC:", 3) == 0) {
                HAL_GPIO_WritePin(MOTOR_DIR_GPIO_Port, MOTOR_DIR_Pin, GPIO_PIN_RESET);
                uint16_t speed = atoi(&rx_buffer[3]);
                __HAL_TIM_SET_COMPARE(&htim16, TIM_CHANNEL_1, speed);
            }
        }
    }
}

#endif // EX_3C_MOTOR_SERIAL
