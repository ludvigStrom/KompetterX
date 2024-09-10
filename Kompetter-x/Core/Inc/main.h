
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx_hal.h"

void Error_Handler(void);


extern uint8_t screenNotUpdated;

#define KEY_COL_1_Pin GPIO_PIN_0
#define KEY_COL_1_GPIO_Port GPIOC
#define KEY_COL_2_Pin GPIO_PIN_1
#define KEY_COL_2_GPIO_Port GPIOC
#define KEY_COL_3_Pin GPIO_PIN_2
#define KEY_COL_3_GPIO_Port GPIOC
#define KEY_COL_4_Pin GPIO_PIN_3
#define KEY_COL_4_GPIO_Port GPIOC
#define LED_STATUS_Pin GPIO_PIN_2
#define LED_STATUS_GPIO_Port GPIOA
#define KEY_ROW_1_Pin GPIO_PIN_4
#define KEY_ROW_1_GPIO_Port GPIOA
#define KEY_ROW_2_Pin GPIO_PIN_5
#define KEY_ROW_2_GPIO_Port GPIOA
#define KEY_ROW_3_Pin GPIO_PIN_6
#define KEY_ROW_3_GPIO_Port GPIOA
#define KEY_ROW_4_Pin GPIO_PIN_7
#define KEY_ROW_4_GPIO_Port GPIOA


#ifdef __cplusplus
}
#endif

#endif
