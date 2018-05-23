/**
********************************************************
*
* @file      Hal_infrared.c
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

#include <stm32f1xx_hal.h>
#include "Hal_infrared.h"
#include <math.h>

void irInit(void)
{
    GPIO_InitTypeDef myGPIO_InitStruct;

    myGPIO_InitStruct.Pin = Infrared_GPIO_Pin;
    myGPIO_InitStruct.Mode = GPIO_MODE_INPUT;/////////////
    myGPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
		//myGPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(Infrared_GPIO_Port, &myGPIO_InitStruct);
}

bool irRead(void)
{
	bool res;
    res=HAL_GPIO_ReadPin(Infrared_GPIO_Port, Infrared_GPIO_Pin);
    return res;

}
