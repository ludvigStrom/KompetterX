#include "main.h"
#include "usb_device.h"

#include "fonts.h"
#include "ssd1306.h"
#include "angleSensor.h"
#include <string.h>
#include "stdio.h"
#include "usbd_hid.h"
#include <stdint.h>
#include "utils.h"
#include "ImprovedKeylayouts.h"
#include "keyboardScanner.h"
#include "usbHidReport.h"
#include "displayManager.h"

extern USBD_HandleTypeDef hUsbDeviceFS;

uint8_t screenNotUpdated = 1;

GPIO_TypeDef* row_ports[NUM_ROWS] = {KEY_ROW_1_GPIO_Port, KEY_ROW_2_GPIO_Port, KEY_ROW_3_GPIO_Port, KEY_ROW_4_GPIO_Port};
uint16_t row_pins[NUM_ROWS] = {KEY_ROW_1_Pin, KEY_ROW_2_Pin, KEY_ROW_3_Pin, KEY_ROW_4_Pin};
GPIO_TypeDef* col_ports[NUM_COLS] = {KEY_COL_1_GPIO_Port, KEY_COL_2_GPIO_Port, KEY_COL_3_GPIO_Port, KEY_COL_4_GPIO_Port};
uint16_t col_pins[NUM_COLS] = {KEY_COL_1_Pin, KEY_COL_2_Pin, KEY_COL_3_Pin, KEY_COL_4_Pin};

I2C_HandleTypeDef hi2c1;
I2C_HandleTypeDef hi2c2;

SPI_HandleTypeDef hspi2;

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_I2C2_Init(void);
static void MX_SPI2_Init(void);

int main(void)
{
  HAL_Init();

  SystemClock_Config();

  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_I2C2_Init();
  MX_USB_DEVICE_Init();
  MX_SPI2_Init();

  HAL_GPIO_TogglePin(LED_STATUS_GPIO_Port, LED_STATUS_Pin); // Toggle state of LED

  HAL_Delay(50);

  usbHidInit(&hUsbDeviceFS);
  keyboardScannerInit();
  angleSensorInit(&hi2c2);

  HAL_GPIO_TogglePin(LED_STATUS_GPIO_Port, LED_STATUS_Pin);

  uint8_t magnetPresent = AS5600_IsMagnetPresent(&hi2c2);

  displayInit();

  while (1)
  {
      angleSensorScrollScan(&hi2c2);
      keyboardScan();

      if (usbHidkeyReportChanged()) {
          usbHidSendKeyboardReport();
      }

      if(smoothedAccumulator != 0){
          usbHidUpdateMouseReport(0, 0, (int8_t)smoothedAccumulator / 35, 0);
          usbHidSendMouseReport();
      }

      displayUpdate(last_key, currentEncoderVal, smoothedAccumulator, magnetPresent);
  }
}

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

static void MX_I2C1_Init(void)
{
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 400000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
}

static void MX_I2C2_Init(void)
{
  hi2c2.Instance = I2C2;
  hi2c2.Init.ClockSpeed = 100000;
  hi2c2.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c2.Init.OwnAddress1 = 0;
  hi2c2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c2.Init.OwnAddress2 = 0;
  hi2c2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c2.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c2) != HAL_OK)
  {
    Error_Handler();
  }

}

static void MX_SPI2_Init(void)
{

  hspi2.Instance = SPI2;
  hspi2.Init.Mode = SPI_MODE_MASTER;
  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    Error_Handler();
  }

}

static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  HAL_GPIO_WritePin(GPIOA, LED_STATUS_Pin|KEY_ROW_1_Pin|KEY_ROW_2_Pin|KEY_ROW_3_Pin
                          |KEY_ROW_4_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : KEY_COL_1_Pin KEY_COL_2_Pin KEY_COL_3_Pin KEY_COL_4_Pin */
  GPIO_InitStruct.Pin = KEY_COL_1_Pin|KEY_COL_2_Pin|KEY_COL_3_Pin|KEY_COL_4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : LED_STATUS_Pin KEY_ROW_1_Pin KEY_ROW_2_Pin KEY_ROW_3_Pin
                           KEY_ROW_4_Pin */
  GPIO_InitStruct.Pin = LED_STATUS_Pin|KEY_ROW_1_Pin|KEY_ROW_2_Pin|KEY_ROW_3_Pin
                          |KEY_ROW_4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

void Error_Handler(void)
{

  __disable_irq();
  while (1)
  {
  }
}

#ifdef  USE_FULL_ASSERT

void assert_failed(uint8_t *file, uint32_t line)
{

}
#endif
