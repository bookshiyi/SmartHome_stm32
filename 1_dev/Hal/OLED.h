#ifndef _OLED_H
#define _OLED_H
#include <stm32f1xx.h>
/*
      oled片选控制   PB0
            TP_NCS   PA4
            TP_SCK   PA5
						TP_MISO  PA6	
						TP_MOSI  PA7	

*/
#define OLED_SCLK                       GPIO_PIN_5     //PA5              
#define OLED_SCLK_GPIO_PORT             GPIOA                        
//#define OLED_SCLK_GPIO_RCC              RCC_APB2Periph_GPIOA

#define OLED_MISO                       GPIO_PIN_6      //PA6               
#define OLED_MISO_GPIO_PORT             GPIOA                         
//#define OLED_MISO_GPIO_RCC              RCC_APB2Periph_GPIOA

#define OLED_MOSI                       GPIO_PIN_7       //PA7             
#define OLED_MOSI_GPIO_PORT             GPIOA                         
//#define OLED_MOSI_GPIO_RCC              RCC_APB2Periph_GPIOA

#define OLED_SCS                        GPIO_PIN_4        //PA4            
#define OLED_SCS_GPIO_PORT              GPIOA                          
//#define OLED_SCS_GPIO_RCC               RCC_APB2Periph_GPIOA


#define SSD_CS_1()	GPIOA->BSRR = GPIO_PIN_4
#define SSD_CS_0()	GPIOA->BRR = GPIO_PIN_4
#define SSD_SDIN_1() GPIOA->BSRR = GPIO_PIN_7
#define SSD_SDIN_0() GPIOA->BRR = GPIO_PIN_7
#define SSD_SCK_1() GPIOA->BSRR = GPIO_PIN_5
#define SSD_SCK_0() GPIOA->BRR = GPIO_PIN_5



/* 字体代码 */
enum
{
	FC_ST_16 = 0,		/* 宋体15x16点阵 （宽x高） */
	FC_ST_12 = 1		/* 宋体12x12点阵 （宽x高） */
};

/* 字体属性结构, 用于LCD_DispStr() */
typedef struct
{
	uint16_t usFontCode;	/* 字体代码 0 表示16点阵 */
	uint16_t usTextColor;	/* 字体颜色 0 或 1 */
	uint16_t usBackColor;	/* 文字背景颜色 0 或 1 */
	uint16_t usSpace;		/* 文字间距，单位 = 像素 */
}FONT_T;


extern  FONT_T tFont12;
extern  FONT_T tFont16;


#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据
/* 可供外部模块调用的函数 */
void OLED_DrawPoint(uint8_t x,uint8_t y,uint8_t t);
void OLED_ShowString(uint8_t x,uint8_t y,const uint8_t *p);
void OLED_DisDigital(uint16_t _usX, uint16_t _usY, uint32_t Dig_Data, FONT_T *_tFont);
void OLED_DisDecimal(uint16_t _usX, uint16_t _usY, double Dig_Data,uint8_t DecimalNum, FONT_T *_tFont);

void OLED_Init(void);
void OLED_InitHard(void);
void OLED_DispOn(void);
void OLED_DispOff(void);
void OLED_StartDraw(void);
void OLED_EndDraw(void);
void OLED_ClrScr(uint8_t _ucMode);
void OLED_DispStr(uint16_t _usX, uint16_t _usY, char *_ptr, FONT_T *_tFont);
void OLED_PutPixel(uint16_t _usX, uint16_t _usY, uint8_t _ucColor);
uint8_t OLED_GetPixel(uint16_t _usX, uint16_t _usY);
void OLED_DrawLine(uint16_t _usX1 , uint16_t _usY1 , uint16_t _usX2 , uint16_t _usY2 , uint8_t _ucColor);
void OLED_DrawPoints(uint16_t *x, uint16_t *y, uint16_t _usSize, uint8_t _ucColor);
void OLED_DrawRect(uint16_t _usX, uint16_t _usY, uint8_t _usHeight, uint16_t _usWidth, uint8_t _ucColor);
void OLED_DrawCircle(uint16_t _usX, uint16_t _usY, uint16_t _usRadius, uint8_t _ucColor);
void OLED_DrawBMP(uint16_t _usX, uint16_t _usY, uint16_t _usHeight, uint16_t _usWidth, uint8_t *_ptr);
#endif


