/**
********************************************************
*
* @file      Hal_RELAY.c
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
#include "hal_relay.h"
#include "delay.h"

void RelayInit(void)
{
    GPIO_InitTypeDef myGPIO_InitStruct;
	
	
    myGPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    myGPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	
    myGPIO_InitStruct.Pin = Relay_1_GPIO_Pin;
    HAL_GPIO_Init(Relay_1_GPIO_Port, &myGPIO_InitStruct);
	
	  myGPIO_InitStruct.Pin = Relay_2_GPIO_Pin;
    HAL_GPIO_Init(Relay_2_GPIO_Port, &myGPIO_InitStruct);
	
	  myGPIO_InitStruct.Pin = Relay_3_GPIO_Pin;
    HAL_GPIO_Init(Relay_3_GPIO_Port, &myGPIO_InitStruct);
	
	  
	  myGPIO_InitStruct.Pin = Relay_4_GPIO_Pin;
    HAL_GPIO_Init(Relay_4_GPIO_Port, &myGPIO_InitStruct);
	
	
		Relay_1_OFF;	
		Relay_2_OFF;	
		Relay_3_OFF;	
		Relay_4_OFF;	
}
void RelayWrite(uint8_t relay,bool status)
{
	switch(relay)
	{
		case 1:
			if(status== true)
			{
			  Relay_1_ON;
			}
			else
			{
				Relay_1_OFF;
			}
			break;
		case 2:
			if(status==1)
			{
			  Relay_2_ON;
			}
			else
			{
				Relay_2_OFF;
			}
			break;
		case 3:
			if(status==1)
			{
			  Relay_3_ON;
			}
			else
			{
				Relay_3_OFF;
			}
			break;
		case 4:
			if(status==1)
			{
			  Relay_4_ON;
			}
			else
			{
				Relay_4_OFF;
			}
			break;
	}
		//printf("relay:%d\n", status);
}

