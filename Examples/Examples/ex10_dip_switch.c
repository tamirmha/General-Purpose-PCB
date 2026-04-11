#include "example_config.h"
#ifdef EX_10_DIP_SWITCH

#include "main.h"



uint8_t dip_value = 0;
uint32_t blink_delay = 500;

void Run_Example(void) {
    
    
    while(1) {
        
        uint8_t bit2 = (HAL_GPIO_ReadPin(DIP1_GPIO_Port, DIP1_Pin) == GPIO_PIN_SET) ? 1 : 0;
        uint8_t bit1 = (HAL_GPIO_ReadPin(DIP2_GPIO_Port, DIP2_Pin) == GPIO_PIN_SET) ? 1 : 0;
        uint8_t bit0 = (HAL_GPIO_ReadPin(DIP3_GPIO_Port, DIP3_Pin) == GPIO_PIN_SET) ? 1 : 0;
        dip_value = (bit2 << 2) | (bit1 << 1) | bit0;
        blink_delay = (dip_value + 1) * 100;

        HAL_GPIO_TogglePin(PCB_LED_GPIO_Port, PCB_LED_Pin);
        HAL_Delay(blink_delay);
    }
}

#endif // EX_10_DIP_SWITCH
