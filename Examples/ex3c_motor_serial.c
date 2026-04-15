#include "example_config.h"
#ifdef EX_3C_MOTOR_SERIAL

#include "main.h"
#include <string.h>
#include <stdlib.h>

extern TIM_HandleTypeDef htim16;
extern UART_HandleTypeDef huart1;

// Make the buffer a bit larger just in case
char rx_buffer[20] = {0};
uint8_t command_ready = 0;

// 1. THIS IS THE MAGIC INTERRUPT FUNCTION!
// The STM32 automatically jumps here the moment your serial message finishes arriving.
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size) {
    if (huart->Instance == USART1) {

        // Tell the main loop that a message is waiting
        command_ready = 1;

        // Immediately start listening for the NEXT message in the background
        HAL_UARTEx_ReceiveToIdle_IT(&huart1, (uint8_t*)rx_buffer, sizeof(rx_buffer));
    }
}

void Run_Example(void) {
    HAL_TIM_PWM_Start(&htim16, TIM_CHANNEL_1);
    
    // 2. Start the very first background listening process before the loop starts
    HAL_UARTEx_ReceiveToIdle_IT(&huart1, (uint8_t*)rx_buffer, sizeof(rx_buffer));

    while(1) {
        // 3. Your while(1) loop is now completely FREE!
        // It never blocks. It only runs this 'if' statement when the interrupt says data is ready.
        
        if (command_ready == 1) {
            if (strncmp(rx_buffer, "CW:", 3) == 0) {
                HAL_GPIO_WritePin(MOTOR_DIR_GPIO_Port, MOTOR_DIR_Pin, GPIO_PIN_SET);
                uint16_t speed = atoi(&rx_buffer[3]);
                __HAL_TIM_SET_COMPARE(&htim16, TIM_CHANNEL_1, speed);

            } else if (strncmp(rx_buffer, "CC:", 3) == 0) {
                HAL_GPIO_WritePin(MOTOR_DIR_GPIO_Port, MOTOR_DIR_Pin, GPIO_PIN_RESET);
                uint16_t speed = atoi(&rx_buffer[3]);
                __HAL_TIM_SET_COMPARE(&htim16, TIM_CHANNEL_1, speed);
            }

            // Clear the buffer and reset the flag so we don't read it twice
            memset(rx_buffer, 0, sizeof(rx_buffer));
            command_ready = 0;
        }

        // You can now blink LEDs or read sensors here without the serial port freezing them!
        HAL_Delay(10);
    }
}

#endif // EX_3C_MOTOR_SERIAL
