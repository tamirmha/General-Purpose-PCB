#include "example_config.h"
#ifdef EX_12_SPI

#include "main.h"

extern SPI_HandleTypeDef hspi2;

uint8_t spi_tx[2] = {0x9F, 0x00};
uint8_t spi_rx[2] = {0};

void Run_Example(void) {
    HAL_GPIO_WritePin(SPI_NCS_GPIO_Port, SPI_NCS_Pin, GPIO_PIN_SET);
    
    while(1) {
        
        HAL_GPIO_WritePin(SPI_NCS_GPIO_Port, SPI_NCS_Pin, GPIO_PIN_RESET);
        HAL_SPI_TransmitReceive(&hspi2, spi_tx, spi_rx, 2, 100);
        HAL_GPIO_WritePin(SPI_NCS_GPIO_Port, SPI_NCS_Pin, GPIO_PIN_SET);
        HAL_Delay(500);
    }
}

#endif // EX_12_SPI
