#include "example_config.h"
#ifdef EX_5_ENCODER

#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern TIM_HandleTypeDef htim1;
extern UART_HandleTypeDef huart1;

// ==========================================
// HARDWARE PARAMETERS
// ==========================================
const int32_t ENCODER_CPR = 64;
const float   GEAR_RATIO = 18.75f;
const int32_t SYSTEM_CPR = (int32_t)(ENCODER_CPR * GEAR_RATIO); // 1200

// ==========================================
// TRACKING & OUTPUT VARIABLES
// ==========================================
int16_t previous_timer_value = 0;
int32_t total_counts = 0;
uint32_t previous_time = 0; // Stopwatch tracker
char tx_buffer[100] = {0};  // Increased size to fit the RPM text

void Run_Example(void) {
    HAL_TIM_Encoder_Start(&htim1, TIM_CHANNEL_ALL);
    
    // Set the initial baselines before the loop starts
    previous_timer_value = (int16_t)__HAL_TIM_GET_COUNTER(&htim1);
    previous_time = HAL_GetTick(); // Start the stopwatch

    while(1) {
        // Check the stopwatch
        uint32_t current_time = HAL_GetTick();
        uint32_t time_diff = current_time - previous_time;

        // Only run the math if exactly 100ms (or more) has passed
        if (time_diff >= 100) {

            // 1. Get current timer value & calculate difference
            int16_t current_timer_value = (int16_t)__HAL_TIM_GET_COUNTER(&htim1);
            int16_t difference = current_timer_value - previous_timer_value;
            total_counts += difference;

            // 2. Reset the baselines for the next 100ms cycle
            previous_timer_value = current_timer_value;
            previous_time = current_time;

            // 3. Calculate Position (Rounds and Degrees)
            int32_t rounds = total_counts / SYSTEM_CPR;
            int32_t degrees = (abs(total_counts) % SYSTEM_CPR) * 360 / SYSTEM_CPR;

            // 4. Calculate Speed (RPM)
            // (Counts in this time interval * 60,000 ms per minute) / (Counts per rev * Time interval)
            int32_t rpm = (difference * 60000) / (SYSTEM_CPR * time_diff);

            // 5. Format and send the data
            sprintf(tx_buffer, "Counts: %ld | Rounds: %ld | Angle: %ld deg | RPM: %ld\r\n",
                    total_counts, rounds, degrees, rpm);
            HAL_UART_Transmit(&huart1, (uint8_t*)tx_buffer, strlen(tx_buffer), HAL_MAX_DELAY);
        }

        // Because we removed HAL_Delay(), the processor is free to do other things
        // thousands of times a second while it waits for the 100ms timer to hit!
    }
}

#endif // EX_5_ENCODER
