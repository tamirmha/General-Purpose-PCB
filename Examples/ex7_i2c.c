#include "example_config.h"
#ifdef EX_7_I2C

#include "main.h"

extern I2C_HandleTypeDef hi2c2;

#define SENSOR_ADDR (0x68 << 1)
uint8_t reg_addr = 0x01;
uint8_t rx_data[2] = {0};

void Run_Example(void) {
    
    
    while(1) {
        
        HAL_I2C_Master_Transmit(&hi2c2, SENSOR_ADDR, &reg_addr, 1, 100);
        HAL_I2C_Master_Receive(&hi2c2, SENSOR_ADDR, rx_data, 2, 100);
        HAL_Delay(500);
    }
}

#endif // EX_7_I2C
