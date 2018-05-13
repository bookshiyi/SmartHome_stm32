/**
********************************************************
*
* @file      hal_buzz.c
* @author    Gizwtis
* @version   V03010100
* @date      2016-07-05
*
* @brief     机智云.只为智能硬件而生
*            Gizwits Smart Cloud  for Smart Products
*            链接|增值ֵ|开放|中立|安全|自有|自由|生态
*            www.gizwits.com
*
*********************************************************/
#include "hal_buzz.h"
#include "delay.h"

void BuzzInit(void)
{
    GPIO_InitTypeDef myGPIO_InitStruct;
	
    myGPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    myGPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    myGPIO_InitStruct.Pin = BUZZ_GPIO_Pin;
    HAL_GPIO_Init(BUZZ_GPIO_Port, &myGPIO_InitStruct);
		BUZZ_OFF;		
}
void Beep(uint16_t times)
{
	uint16_t t;
	for(t=0;t<times;t++)
	{
		BUZZ_ON;
		Delay_us(500);
		BUZZ_OFF;
		Delay_us(500);
	}
}
void BuzzWrite(uint16_t nms)
{
	  Beep(nms);
		printf("BUZZ:%d\n", nms);
}

