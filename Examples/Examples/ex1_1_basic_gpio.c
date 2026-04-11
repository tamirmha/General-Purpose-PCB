#include "example_config.h"
#ifdef EX_1_1_BASIC_GPIO

#include "main.h"

// Tell this file that htim14 exists over in main.c!
extern TIM_HandleTypeDef htim14;

void Run_Example(void) {
    // 1. Create a variable to remember if the solenoid is currently ON (1) or OFF (0)
    uint8_t solenoid_on = 0;
    
    // 2. Start the Timer in the background (Default to 0% power / OFF)
    HAL_TIM_PWM_Start(&htim14, TIM_CHANNEL_1);
    __HAL_TIM_SET_COMPARE(&htim14, TIM_CHANNEL_1, 0);

    while(1) {
    	if (solenoid_on)  // When solonoid is already high lower the voltage to keep it from warm
			__HAL_TIM_SET_COMPARE(&htim14, TIM_CHANNEL_1, 32000); // 100% ON
        // Check if the button was just pressed (pulled to Ground)
        if (HAL_GPIO_ReadPin(BTN1_GPIO_Port, BTN1_Pin) == GPIO_PIN_RESET) {

            // Flip our tracking variable (0 becomes 1, 1 becomes 0)
            solenoid_on = !solenoid_on;

            // Update the hardware based on the new state
            if (solenoid_on)	__HAL_TIM_SET_COMPARE(&htim14, TIM_CHANNEL_1, 65535); // 100% ON
            else				__HAL_TIM_SET_COMPARE(&htim14, TIM_CHANNEL_1, 0);     // 0% OFF

            // Toggle the User LED so we have a visual indicator
            HAL_GPIO_TogglePin(PCB_LED_GPIO_Port, PCB_LED_Pin);

            // 3. WAIT FOR THE USER TO LET GO OF THE BUTTON!
            // The code traps itself here until the button reads HIGH (released) again
            while(HAL_GPIO_ReadPin(BTN1_GPIO_Port, BTN1_Pin) == GPIO_PIN_RESET)  HAL_Delay(10);

            // A tiny extra delay to prevent mechanical button bounce
            HAL_Delay(100);
        }
    }
}

#endif // EX_1_BASIC_GPIO
