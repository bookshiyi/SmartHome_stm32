#ifndef _HAL_BUZZ_H
#define _HAL_BUZZ_H

#include "stdbool.h"
#include <stdio.h>
#include <stm32f1xx.h>
#include <stm32f1xx_hal.h>
#include <stm32f1xx_hal_gpio.h>


#define BUZZ_GPIO_Port         GPIOA
#define BUZZ_GPIO_Pin          GPIO_PIN_1


#define BUZZ_OFF 		HAL_GPIO_WritePin(BUZZ_GPIO_Port, BUZZ_GPIO_Pin, GPIO_PIN_SET)
#define BUZZ_ON 		HAL_GPIO_WritePin(BUZZ_GPIO_Port, BUZZ_GPIO_Pin, GPIO_PIN_RESET)                                                  

void BuzzInit(void);
void BuzzWrite(uint16_t nms);
void Beep(uint16_t times);

#endif /*_HAL_RGB_LED_H*/

