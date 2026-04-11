#include "example_config.h"
#ifdef EX_1_BASIC_GPIO

#include "main.h"

// Tell this file that htim14 exists over in main.c!
extern TIM_HandleTypeDef htim14;

void Run_Example(void) {
    
    while(1) {
        // Look for GPIO_PIN_RESET because the button pulls to Ground
        if (HAL_GPIO_ReadPin(BTN1_GPIO_Port, BTN1_Pin) == GPIO_PIN_RESET) {

            // Turn on Solenoid using PWM (100% duty cycle)
            HAL_TIM_PWM_Start(&htim14, TIM_CHANNEL_1);
            __HAL_TIM_SET_COMPARE(&htim14, TIM_CHANNEL_1, 65535);

            // Toggle the User LED
            HAL_GPIO_TogglePin(PCB_LED_GPIO_Port, PCB_LED_Pin);

            HAL_Delay(200); // Simple debounce

        } else {
            // Turn off Solenoid using PWM (0% duty cycle)
            __HAL_TIM_SET_COMPARE(&htim14, TIM_CHANNEL_1, 0);
        }
    }
}

#endif // EX_1_BASIC_GPIO
