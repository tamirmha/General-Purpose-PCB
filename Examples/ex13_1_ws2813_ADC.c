#include "example_config.h"
#ifdef EX_13_1_WS2812_ADC

#include "main.h"
#include <stdlib.h>

extern ADC_HandleTypeDef hadc1;
extern TIM_HandleTypeDef htim3;

#define NUM_LEDS 9

// --- FIX 1: INCREASE RESET PULSE ---
// Modern WS2812B chips require >280us of silence to latch the colors.
// 250 pulses * 1.25us = 312us of perfectly clean reset time!
#define RESET_PULSE 250
#define DMA_BUFF_SIZE ((NUM_LEDS * 24) + RESET_PULSE)

#define WS2812_0_BIT 26
#define WS2812_1_BIT 53

uint32_t pwm_dma_buffer[DMA_BUFF_SIZE] = {0};
uint32_t adc_value = 0;

void WS2812_SetColor(uint16_t led_index, uint8_t r, uint8_t g, uint8_t b, uint32_t raw_adc) {
    if(led_index >= NUM_LEDS) return;

    // Dead zone for potentiometer noise at the bottom
    if (raw_adc < 150)        	raw_adc = 0;
    // Cap at 1365 due to the board's 1/3 hardware voltage divider
    if (raw_adc > 2068)         raw_adc = 2068;

    // Scale the colors based on the ADC brightness
    uint32_t bright_r = (r * raw_adc) / 2068;
    uint32_t bright_g = (g * raw_adc) / 2068;
    uint32_t bright_b = (b * raw_adc) / 2068;

    // Combine into WS2812 format (Green-Red-Blue)
    uint32_t color = (bright_g << 16) | (bright_r << 8) | bright_b;
    uint32_t start_idx = led_index * 24;

    for (int i = 23; i >= 0; i--) {
        if (color & (1 << i))	pwm_dma_buffer[start_idx + (23 - i)] = WS2812_1_BIT;
        else             		pwm_dma_buffer[start_idx + (23 - i)] = WS2812_0_BIT;
    }
}

void WS2812_Update(void) {
    // --- FIX 2: STOP BEFORE STARTING ---
    // Ensure the STM32 totally clears the previous DMA transfer before kicking off a new one
    HAL_TIM_PWM_Stop_DMA(&htim3, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start_DMA(&htim3, TIM_CHANNEL_1, (uint32_t *)pwm_dma_buffer, DMA_BUFF_SIZE);
}

void Run_Example(void) {
    
    while(1) {
        HAL_ADC_Start(&hadc1);
        if (HAL_ADC_PollForConversion(&hadc1, 10) == HAL_OK) {
            adc_value = HAL_ADC_GetValue(&hadc1);
        }
        HAL_ADC_Stop(&hadc1);
        // Generate 3 random numbers between 0 and 255

        // Your pure white LED test (255, 255, 255)
        for(int i = 0; i < NUM_LEDS; i++)
        {
            uint8_t rand_r = rand() % 256;
            uint8_t rand_g = rand() % 256;
            uint8_t rand_b = rand() % 256;
        	WS2812_SetColor(i, rand_r, rand_g, rand_b, adc_value);
        }

        WS2812_Update();

        HAL_Delay(500);
    }
}

#endif // EX_13_1_WS2812_ADC
