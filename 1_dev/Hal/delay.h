#ifndef __DELAY_H
#define __DELAY_H 	

#include <stm32f103xb.h>
#include <stm32f1xx.h>
#include <stm32f1xx_hal.h>

void delayInit(uint8_t SYSCLK);
void delay_ms(uint16_t nms);
void delay_us(uint32_t nus);
void Delay_us(uint16_t nus);
void Delay_ms(uint16_t nms);

#endif 

