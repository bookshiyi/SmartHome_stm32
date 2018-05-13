/**
********************************************************
*
* @file      delay.c
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

#include "delay.h"
#include "sys.h"

static uint8_t  facUs=0;																		//us延时倍乘数
static uint16_t facMs=0;																		//ms延时倍乘数

void delayInit(uint8_t SYSCLK)
{
    HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);	//选择外部时钟,HCLK/8
    facUs=SYSCLK/8; //硬件分频,fac_us得出的值要给下面的时钟函数使用
    facMs =(uint16_t)facUs*1000;
}

void delay_us(uint32_t nus)
{
    uint32_t temp;  
    SysTick->LOAD = nus*facUs;  //延时10us,10*9 = 90,装到load寄存器中
    SysTick->VAL=0x00;//计数器清0
    SysTick->CTRL = 0x01;//配置异常生效,也就是计数器倒数到0时发出异常通知
    do  
    {  
         temp = SysTick->CTRL;//时间到,该位将被硬件置1,但被查询后自动清0
    }  
    while(temp & 0x01 && !(temp &(1<<16)));//查询
    SysTick->CTRL = 0x00;//关闭定时器
    SysTick->VAL = 0x00;//清空val,清空定时器
}


void delay_ms(uint16_t nms)
{
    uint32_t temp;  
    SysTick->LOAD = nms*facMs;//延时10ms,10*9 = 90,装到load寄存器中
    SysTick->VAL=0x00;//计数器清0
    SysTick->CTRL = 0x01;//配置异常生效,也就是计数器倒数到0时发出异常通知
    do  
    {  
         temp = SysTick->CTRL;//时间到,该位将被硬件置1,但被查询后自动清0
    }  
    while(temp & 0x01 && !(temp &(1<<16)));//查询

    SysTick->CTRL = 0x00;//关闭定时器
    SysTick->VAL = 0x00;//清空val,清空定时器
}

void Delay_us(uint16_t nus)
{
	uint16_t i,j;
	for(i=0;i<nus;i++)
		for(j=0;j<8;j++);
}
void Delay_ms(uint16_t nms)
{
	uint16_t i,j;
	for(i=0;i<nms;i++)
		for(j=0;j<8000;j++);
}