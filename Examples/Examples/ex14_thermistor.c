#include "example_config.h"
#ifdef EX_14_THERMISTOR

#include "main.h"

extern ADC_HandleTypeDef hadc1;

#include <math.h>

uint32_t adc_value = 0;
float R_thermistor = 0;
float temperature_C = 0;

const float SERIES_RESISTOR = 10000.0;
const float NOMINAL_RESISTANCE = 10000.0;
const float NOMINAL_TEMPERATURE = 298.15;
const float B_COEFFICIENT = 3950.0;

void Run_Example(void) {
    
    
    while(1) {
        
        HAL_ADC_Start(&hadc1);
        if (HAL_ADC_PollForConversion(&hadc1, 10) == HAL_OK) {
            adc_value = HAL_ADC_GetValue(&hadc1);
        }
        HAL_ADC_Stop(&hadc1);

        if (adc_value > 0 && adc_value < 4095) {
            R_thermistor = SERIES_RESISTOR / ((4095.0 / (float)adc_value) - 1.0);
            float steinhart;
            steinhart = R_thermistor / NOMINAL_RESISTANCE;
            steinhart = log(steinhart);
            steinhart /= B_COEFFICIENT;
            steinhart += 1.0 / NOMINAL_TEMPERATURE;
            steinhart = 1.0 / steinhart;
            temperature_C = steinhart - 273.15;                
        }
        HAL_Delay(500);
    }
}

#endif // EX_14_THERMISTOR
