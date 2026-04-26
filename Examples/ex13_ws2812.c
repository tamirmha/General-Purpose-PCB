#include "example_config.h"
#ifdef EX_13_WS2812

#include "main.h"


extern TIM_HandleTypeDef htim3;


#define NUM_LEDS 10
#define RESET_PULSE 40 
#define DMA_BUFF_SIZE ((NUM_LEDS * 24) + RESET_PULSE)
#define WS2812_0_BIT 26
#define WS2812_1_BIT 53

uint32_t pwm_dma_buffer[DMA_BUFF_SIZE] = {0};

void WS2812_SetColor(uint16_t led_index, uint8_t r, uint8_t g, uint8_t b) {
    if(led_index >= NUM_LEDS) return;
    uint32_t color = (g << 16) | (r << 8) | b; 
    uint32_t start_idx = led_index * 24;
    for (int i = 23; i >= 0; i--) {
        if (color & (1 << i))
            pwm_dma_buffer[start_idx + (23 - i)] = WS2812_1_BIT;
         else
            pwm_dma_buffer[start_idx + (23 - i)] = WS2812_0_BIT;
    }
}
void WS2812_Update(void) {
    HAL_TIM_PWM_Start_DMA(&htim3, TIM_CHANNEL_1, (uint32_t *)pwm_dma_buffer, DMA_BUFF_SIZE);
}

void Run_Example(void) {
    
    while(1) {
        for(int i = 0; i < NUM_LEDS; i++)
		  {
			uint8_t rand_r = rand() % 64;
			uint8_t rand_g = rand() % 64;
			uint8_t rand_b = rand() % 64;
			WS2812_SetColor(i, rand_r, rand_g, rand_b);
		  }
	   WS2812_Update();
       HAL_Delay(500);
    }
}

#endif // EX_13_WS2812
