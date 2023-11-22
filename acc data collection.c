#include "main.h"
#include "fatfs.h"
#include "stm32f4xx_hal.h"
#define adxl_address 0x53<<1
#define BUZZER_PIN GPIO_PIN_8
#define BUZZER_PORT GPIOA
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_I2C1_Init(void);
uint8_t data_rec[6];
uint16_t x,y,z;
float xg,yg,zg;

void adxl_write(uint8_t reg, uint8_t value){
	uint8_t data[2];
	data[0]=reg;
	data[1]=value;
	HAL_I2C_Master_Transmit(&hi2c1, adxl_address, data, 2, 10);
}

void adxl_read (uint8_t reg, uint8_t value)
{
   HAL_I2C_Mem_Read (&hi2c1, adxl_address, reg, 1, data_rec, value, 100);
}

void adxl_init(void){
	adxl_read (0x00, 1);
	adxl_write(0x2d, 0);
	adxl_write(0x2d, 0x08);
	adxl_write(0x31, 0x01);
}
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_FATFS_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */
  adxl_init ();
while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  adxl_read (0x32, 6);
	  x = ((data_rec[1]<<8)|data_rec[0]);
	  y = ((data_rec[3]<<8)|data_rec[2]);
	  z = ((data_rec[5]<<8)|data_rec[4]);
	  xg = x * .0078;
	  yg = y * .0078;
	  zg = z * .0078;
	  HAL_Delay(100);


  }
  /* USER CODE END 3 */
}
