/**
********************************************************
*
* @file      Hal_rgb_led.c
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
#include "hal_led.h"
#include "delay.h"

void LedInit(void)
{
    GPIO_InitTypeDef myGPIO_InitStruct;
	
	
    myGPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    myGPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	
    myGPIO_InitStruct.Pin = LED1_GPIO_Pin;
    HAL_GPIO_Init(LED1_GPIO_Port, &myGPIO_InitStruct);
	
	  myGPIO_InitStruct.Pin = LED2_GPIO_Pin;
    HAL_GPIO_Init(LED2_GPIO_Port, &myGPIO_InitStruct);
	
	  myGPIO_InitStruct.Pin = LED3_GPIO_Pin;
    HAL_GPIO_Init(LED3_GPIO_Port, &myGPIO_InitStruct);
	
	
		LED1_OFF;	
		LED2_OFF;	
		LED3_OFF;	
}
void LedWrite(uint8_t led,bool status)
{
	switch(led)
	{
		case 1:
			if(status== true)
			{
			  LED1_ON;
			}
			else
			{
				LED1_OFF;
			}
			break;
		case 2:
			if(status==1)
			{
			  LED2_ON;
			}
			else
			{
				LED2_OFF;
			}
			break;
		case 3:
			if(status==1)
			{
			  LED3_ON;
			}
			else
			{
				LED3_OFF;
			}
			break;
	}
		//printf("led:%d\n", status);
}

