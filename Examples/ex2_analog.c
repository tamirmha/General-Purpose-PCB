#include "example_config.h"
#ifdef EX_2_ANALOG

#include "main.h"

extern ADC_HandleTypeDef hadc1;
extern DAC_HandleTypeDef hdac1;

uint32_t adc_value = 0;

void Run_Example(void) {
    
    // Start the DAC in the background
    HAL_DAC_Start(&hdac1, DAC_CHANNEL_1);
    
    while(1) {
        // 1. Read the Analog Input (Potentiometer)
        HAL_ADC_Start(&hadc1);
        if (HAL_ADC_PollForConversion(&hadc1, 10) == HAL_OK) {
            adc_value = HAL_ADC_GetValue(&hadc1);
        }
        HAL_ADC_Stop(&hadc1);

        // 2. Mirror that exact value out to the DAC!
        HAL_DAC_SetValue(&hdac1, DAC_CHANNEL_1, DAC_ALIGN_12B_R, adc_value);

        HAL_Delay(50);
    }
}

#endif // EX_2_ANALOG
