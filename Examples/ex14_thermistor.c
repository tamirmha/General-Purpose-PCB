#include "example_config.h"
#ifdef EX_14_THERMISTOR

#include "main.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

// 1. Bring in the hardware handles
extern ADC_HandleTypeDef hadc1;
extern UART_HandleTypeDef huart1;

// 2. Global Variables and Constants
float R_thermistor = 0;
float temperature_C = 0;
char serial_buffer[100];

const float SERIES_RESISTOR = 100000.0;
const float NOMINAL_RESISTANCE = 100000.0;
const float NOMINAL_TEMPERATURE = 298.15;
const float B_COEFFICIENT = 3950.0;


uint32_t Read_ADC_Channel(uint32_t channel) {
    ADC_ChannelConfTypeDef sConfig = {0};

    // Configure the internal switch to point to the requested channel
    sConfig.Channel = channel;
    sConfig.Rank = ADC_REGULAR_RANK_1;
    sConfig.SamplingTime = ADC_SAMPLINGTIME_COMMON_1;
    HAL_ADC_ConfigChannel(&hadc1, &sConfig);

    // Give the hardware a tiny moment to stabilize
    for (volatile int i = 0; i < 100; i++) {}

    // --- NEW: SOFTWARE FILTERING (AVERAGING) ---
    uint32_t total_adc_value = 0;
    const int NUM_SAMPLES = 16; // Take 16 rapid-fire readings

    for (int i = 0; i < NUM_SAMPLES; i++) {
        HAL_ADC_Start(&hadc1);
        HAL_ADC_PollForConversion(&hadc1, 10);
        total_adc_value += HAL_ADC_GetValue(&hadc1);
        HAL_ADC_Stop(&hadc1);
    }

    // Divide the total by the number of samples to get the smooth average
    return (total_adc_value / NUM_SAMPLES);
}
// ---------------------------------------------------------


// 4. Your Main Example Function
void Run_Example(void) {
    
    char *startup_msg = "Starting Dual ADC Reading...\r\n";
    HAL_UART_Transmit(&huart1, (uint8_t*)startup_msg, strlen(startup_msg), HAL_MAX_DELAY);

    while(1) {
        
        // Use the helper function to read the Thermistor (PB1 = IN9)
        uint32_t therm_value = Read_ADC_Channel(ADC_CHANNEL_9);

        // --- PROCESS THERMISTOR MATH ---
        if (therm_value > 0 && therm_value < 4095) {

            R_thermistor = SERIES_RESISTOR / ((4095.0 / (float)therm_value) - 1.0);

            float steinhart = R_thermistor / NOMINAL_RESISTANCE;
            steinhart = log(steinhart);
            steinhart /= B_COEFFICIENT;
            steinhart += 1.0 / NOMINAL_TEMPERATURE;
            steinhart = 1.0 / steinhart;
            temperature_C = steinhart - 273.15;                

            // Extract whole numbers and decimals to avoid float printing issues
            int temp_whole = (int)temperature_C;
            int temp_decimal = (int)((temperature_C - temp_whole) * 10);
            if (temp_decimal < 0) temp_decimal = -temp_decimal;

            // Print BOTH values!
            sprintf(serial_buffer, "Therm ADC: %lu | Temp: %d.%01d C\r\n",
            		 therm_value, temp_whole, temp_decimal);

            HAL_UART_Transmit(&huart1, (uint8_t*)serial_buffer, strlen(serial_buffer), HAL_MAX_DELAY);
        }

        HAL_Delay(500);
    }
}

#endif // EX_14_THERMISTOR
