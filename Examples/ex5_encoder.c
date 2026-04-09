#include "example_config.h"
#ifdef EX_5_ENCODER

#include "main.h"

extern TIM_HandleTypeDef htim1;

int32_t encoder_count = 0;

void Run_Example(void) {
    HAL_TIM_Encoder_Start(&htim1, TIM_CHANNEL_ALL);
    
    while(1) {
        encoder_count = __HAL_TIM_GET_COUNTER(&htim1);
HAL_Delay(100);
    }
}

#endif // EX_5_ENCODER
