#ifndef _HAL_RELAY_H
#define _HAL_RELAY_H

#include "stdbool.h"
#include <stdio.h>
#include <stm32f1xx.h>
#include <stm32f1xx_hal.h>
#include <stm32f1xx_hal_gpio.h>


//¿Õµ÷
//¼ÓÊªÆ÷
//ÈÈË®Æ÷
//Ðþ¹ØµÆ£¬°åÔØ¼ÌµçÆ÷

#define Relay_1_GPIO_Port         GPIOB
#define Relay_1_GPIO_Pin          GPIO_PIN_6

#define Relay_2_GPIO_Port         GPIOA
#define Relay_2_GPIO_Pin          GPIO_PIN_12

#define Relay_3_GPIO_Port         GPIOA
#define Relay_3_GPIO_Pin          GPIO_PIN_15

#define Relay_4_GPIO_Port         GPIOB
#define Relay_4_GPIO_Pin          GPIO_PIN_3


#define Relay_1_OFF 	HAL_GPIO_WritePin(Relay_1_GPIO_Port, Relay_1_GPIO_Pin, GPIO_PIN_SET)
#define Relay_1_ON 		HAL_GPIO_WritePin(Relay_1_GPIO_Port, Relay_1_GPIO_Pin, GPIO_PIN_RESET)                                                  
#define Relay_2_OFF 	HAL_GPIO_WritePin(Relay_2_GPIO_Port, Relay_2_GPIO_Pin, GPIO_PIN_SET)
#define Relay_2_ON 		HAL_GPIO_WritePin(Relay_2_GPIO_Port, Relay_2_GPIO_Pin, GPIO_PIN_RESET)                                                 
#define Relay_3_OFF 	HAL_GPIO_WritePin(Relay_3_GPIO_Port, Relay_3_GPIO_Pin, GPIO_PIN_SET)
#define Relay_3_ON 		HAL_GPIO_WritePin(Relay_3_GPIO_Port, Relay_3_GPIO_Pin, GPIO_PIN_RESET)                                               
#define Relay_4_OFF 	HAL_GPIO_WritePin(Relay_4_GPIO_Port, Relay_4_GPIO_Pin, GPIO_PIN_SET)
#define Relay_4_ON 		HAL_GPIO_WritePin(Relay_4_GPIO_Port, Relay_4_GPIO_Pin, GPIO_PIN_RESET)


void RelayInit(void);
void RelayWrite(uint8_t relay,bool status);


#endif /*_HAL_RGB_LED_H*/

