#include "stm32f4xx_hal.h"

// Define the GPIO pin connected to the buzzer
#define BUZZER_PIN GPIO_PIN_0
#define BUZZER_PORT GPIOA

// Function to initialize the buzzer GPIO pin
void Buzzer_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // Enable GPIO clock
    __HAL_RCC_GPIOA_CLK_ENABLE();

    // Configure the GPIO pin
    GPIO_InitStruct.Pin = BUZZER_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

    HAL_GPIO_Init(BUZZER_PORT, &GPIO_InitStruct);

    // Turn off the buzzer initially
    HAL_GPIO_WritePin(BUZZER_PORT, BUZZER_PIN, GPIO_PIN_RESET);
}

// Function to make the buzzer ring at a specific frequency for a certain duration
void Buzzer_Ring(uint16_t frequency, uint32_t duration_ms) {
    // Calculate the half-period of the square wave
    uint32_t half_period_us = 1000000 / (2 * frequency);

    // Calculate the number of toggles needed for the specified duration
    uint32_t num_toggles = (duration_ms * 1000) / (2 * half_period_us);

    // Toggle the buzzer pin to generate the square wave
    for (uint32_t i = 0; i < num_toggles; ++i) {
        HAL_GPIO_TogglePin(BUZZER_PORT, BUZZER_PIN);
        HAL_Delay(half_period_us / 1000); // Convert microseconds to milliseconds
    }

    // Turn off the buzzer
    HAL_GPIO_WritePin(BUZZER_PORT, BUZZER_PIN, GPIO_PIN_RESET);
}
