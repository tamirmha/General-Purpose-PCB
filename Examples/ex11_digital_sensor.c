#include "example_config.h"
#ifdef EX_11_DIGITAL_SENSOR

#include "main.h"



uint8_t current_state = 0;
uint8_t prev_state = 0;
uint32_t object_counter = 0;

void Run_Example(void) {
    
    
    while(1) {
        
        current_state = HAL_GPIO_ReadPin(DIGITAL_SENS_GPIO_Port, DIGITAL_SENS_Pin);
        if (current_state == GPIO_PIN_SET) {
            HAL_GPIO_WritePin(PCB_LED_GPIO_Port, PCB_LED_Pin, GPIO_PIN_SET);
        } else {
            HAL_GPIO_WritePin(PCB_LED_GPIO_Port, PCB_LED_Pin, GPIO_PIN_RESET);
        }
        if ((current_state == GPIO_PIN_SET) && (prev_state == GPIO_PIN_RESET)) {
            object_counter++;
        }
        prev_state = current_state;
        HAL_Delay(10);
    }
}

#endif // EX_11_DIGITAL_SENSOR
