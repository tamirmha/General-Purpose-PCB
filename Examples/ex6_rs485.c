#include "example_config.h"
#ifdef EX_6_RS485

#include "main.h"

extern UART_HandleTypeDef huart2;

char tx_msg[] = "Hello RS485\r\n";

void Run_Example(void) {
    
    
    while(1) {
        
        // Because PA1 is configured as USART2_DE (Hardware Flow Control), 
        // the STM32 toggles the Drive Enable pin automatically!
        HAL_UART_Transmit(&huart2, (uint8_t*)tx_msg, strlen(tx_msg), 100);
        HAL_Delay(1000);
    }
}

#endif // EX_6_RS485
