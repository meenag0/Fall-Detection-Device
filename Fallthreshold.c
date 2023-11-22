#include "main.h"
#include "stm32f4xx_hal.h"
#include "fatfs.h"

#define adxl_address 0x53<<1
#define BUZZER_PIN GPIO_PIN_8
#define BUZZER_PORT GPIOA

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_I2C1_Init(void);

uint8_t data_rec[6];
uint16_t x, y, z;
float xg, yg, zg;

// Buzzer functions
void Buzzer_Init(void);
void Buzzer_Ring(uint16_t frequency, uint32_t duration_ms);

// ADXL accelerometer functions
void adxl_write(uint8_t reg, uint8_t value);
void adxl_read(uint8_t reg, uint8_t value);
void adxl_init(void);

// Free fall detection threshold (adjust as needed)
#define FREE_FALL_THRESHOLD 500

int main(void) {
    // Initialization code ...

    // Initialize ADXL accelerometer and buzzer
    adxl_init();
    Buzzer_Init();

    while (1) {
        // Read accelerometer data
        adxl_read(0x32, 6);
        x = ((data_rec[1] << 8) | data_rec[0]);
        y = ((data_rec[3] << 8) | data_rec[2]);
        z = ((data_rec[5] << 8) | data_rec[4]);

        // Convert raw data to gravitational units
        xg = x * 0.0078;
        yg = y * 0.0078;
        zg = z * 0.0078;

        // Calculate the magnitude of acceleration
        float acceleration_magnitude = sqrt(xg * xg + yg * yg + zg * zg);

        // Check if the magnitude exceeds the free fall threshold
        if (acceleration_magnitude < FREE_FALL_THRESHOLD) {
            // Ring the buzzer with a specific frequency and duration
            Buzzer_Ring(1000, 500);  // Adjust frequency and duration as needed
        }

        // Delay for stability (adjust as needed)
        HAL_Delay(100);
    }
}
