#include "example_config.h"
#ifdef EX_13_WS2812

#include "main.h"

extern TIM_HandleTypeDef htim3;


#define NUM_LEDS 5 
#define RESET_PULSE 40 
#define DMA_BUFF_SIZE ((NUM_LEDS * 24) + RESET_PULSE)
// PWM duty cycle values (Assuming ARR = 19 for a 16MHz clock)
#define WS2812_0_BIT 6   // ~33% duty cycle for a '0'
#define WS2812_1_BIT 13  // ~66% duty cycle for a '1'
uint32_t pwm_dma_buffer[DMA_BUFF_SIZE] = {0};

void WS2812_SetColor(uint16_t led_index, uint8_t r, uint8_t g, uint8_t b) {
    if(led_index >= NUM_LEDS) return;
    uint32_t color = (g << 16) | (r << 8) | b; 
    uint32_t start_idx = led_index * 24;
    for (int i = 23; i >= 0; i--) {
        if (color & (1 << i)) {
            pwm_dma_buffer[start_idx + (23 - i)] = WS2812_1_BIT;
        } else {
            pwm_dma_buffer[start_idx + (23 - i)] = WS2812_0_BIT;
        }
    }
}
void WS2812_Update(void) {
    HAL_TIM_PWM_Start_DMA(&htim3, TIM_CHANNEL_1, (uint32_t *)pwm_dma_buffer, DMA_BUFF_SIZE);
}

void Run_Example(void) {
    
        WS2812_SetColor(0, 255, 255, 255);
//        WS2812_SetColor(1, 0, 255, 0);
        WS2812_Update();
    
    while(1) {
        HAL_Delay(100);
    }
}

#endif // EX_13_WS2812
