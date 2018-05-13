#ifndef _HAL_LED_H
#define _HAL_LED_H

#include "stdbool.h"
#include <stdio.h>
#include <stm32f1xx.h>
#include <stm32f1xx_hal.h>
#include <stm32f1xx_hal_gpio.h>


#define LED1_GPIO_Port         GPIOC
#define LED1_GPIO_Pin          GPIO_PIN_13

#define LED2_GPIO_Port         GPIOB
#define LED2_GPIO_Pin          GPIO_PIN_0

#define LED3_GPIO_Port         GPIOB
#define LED3_GPIO_Pin          GPIO_PIN_1



#define LED1_OFF 	HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_GPIO_Pin, GPIO_PIN_SET)
#define LED1_ON 	HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_GPIO_Pin, GPIO_PIN_RESET)                                                  
#define LED2_OFF 	HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_GPIO_Pin, GPIO_PIN_SET)
#define LED2_ON 	HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_GPIO_Pin, GPIO_PIN_RESET)                                                 
#define LED3_OFF 	HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_GPIO_Pin, GPIO_PIN_SET)
#define LED3_ON 	HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_GPIO_Pin, GPIO_PIN_RESET)


void LedInit(void);
void LedWrite(uint8_t led,bool status);


#endif /*_HAL_RGB_LED_H*/

