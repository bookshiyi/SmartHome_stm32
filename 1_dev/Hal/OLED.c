/******************** (C) COPYRIGHT  Ô´µØ¹¤×÷ÊÒ ********************************
 * ÎÄ¼şÃû  £ºOLED.c
 * ÃèÊö    £º¹ØÓÚOLEDµÄ³õÊ¼»¯¡¢Çı¶¯µÈ  
 * ×÷Õß    £ºzhuoyingxingyu
 * ÌÔ±¦    £ºÔ´µØ¹¤×÷ÊÒhttp://vcc-gnd.taobao.com/
 * ÂÛÌ³µØÖ·£º¼«¿ÍÔ°µØ-Ç¶ÈëÊ½¿ª·¢ÂÛÌ³http://vcc-gnd.com/
 * °æ±¾¸üĞÂ: 2016-04-08
 * Ó²¼şÁ¬½Ó:
          //oledÆ¬Ñ¡¿ØÖÆ   PB0
            TP_NCS   PA4
            TP_SCK   PA5
						TP_MISO  PA6	
						TP_MOSI  PA7						
 * µ÷ÊÔ·½Ê½£ºJ-Link-OB
********************************************************************************/
#include <stdio.h>
#include <string.h>
#include "OLED.h"
#include "fonts.h"
#include <math.h>
FONT_T tFont12, tFont16;

//#define TRUN_180_EN			/* ·­×ª180¶È */
void OLED_WR_Byte(uint8_t dat,uint8_t cmd);
static void OLED_ConfigGPIO(void);
static void OLED_BufToPanel(void);
/* 12864 OLEDµÄÏÔ´æ¾µÏñ£¬Õ¼ÓÃ1K×Ö½Ú. ¹²8ĞĞ£¬Ã¿ĞĞ128ÏñËØ */
/* ÎªÁË±ÜÃâË¢ÆÁÀ­Ä»¸ĞÌ«Ç¿£¬ÒıÈëË¢ÆÁ±êÖ¾¡£
0 ±íÊ¾ÏÔÊ¾º¯ÊıÖ»¸ÄĞ´»º³åÇø£¬²»Ğ´ÆÁ¡£1 ±íÊ¾Ö±½ÓĞ´ÆÁ£¨Í¬Ê±Ğ´»º³åÇø£© */
static uint8_t s_ucUpdateEn = 1;
static uint8_t s_ucGRAM[8][128];
void  OLEDDelay (uint32_t nCount)
{
  for(; nCount != 0; nCount--);
}

 /**
  * @file   OLED_Refresh_Gram
  * @brief  ¸üĞÂÏÔ´æµ½LCD	
  * @param  ÎŞ
  * @retval ÎŞ
  */
void OLED_Refresh_Gram(void)
{
  uint8_t i,n;		    
  for(i=0;i<8;i++)  
  {  
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //ÉèÖÃÒ³µØÖ·£¨0~7£©
		OLED_WR_Byte (0x00,OLED_CMD);      //ÉèÖÃÏÔÊ¾Î»ÖÃ¡ªÁĞµÍµØÖ·
		OLED_WR_Byte (0x10,OLED_CMD);      //ÉèÖÃÏÔÊ¾Î»ÖÃ¡ªÁĞ¸ßµØÖ·    
		for(n=0;n<128;n++)OLED_WR_Byte(s_ucGRAM[i][n],OLED_DATA); 
  }   
}
 /**
  * @file   OLED_ConfigGPIO
  * @brief  ÅäÖÃOLED¿ØÖÆ¿ÚÏß£¬ÉèÖÃÎª8Î»80XX×ÜÏß¿ØÖÆÄ£Ê½»òSPIÄ£Ê½
  * @param  ÎŞ
  * @retval ÎŞ
  */
static void OLED_ConfigGPIO(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
	
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
		
    GPIO_InitStructure.Pin = OLED_SCS;
	  HAL_GPIO_Init(OLED_SCS_GPIO_PORT, &GPIO_InitStructure);
	
	  GPIO_InitStructure.Pin = OLED_SCLK;
	  HAL_GPIO_Init(OLED_SCLK_GPIO_PORT, &GPIO_InitStructure);
	
	  GPIO_InitStructure.Pin = OLED_MISO;
	  HAL_GPIO_Init(OLED_MISO_GPIO_PORT, &GPIO_InitStructure);
	
	  GPIO_InitStructure.Pin = OLED_MOSI;
	  HAL_GPIO_Init(OLED_MOSI_GPIO_PORT, &GPIO_InitStructure);
    SSD_CS_1();
   
}

 /**
  * @file   OLED_InitHard
  * @brief  OLEDÆÁÓ²¼ş³õÊ¼»¯
  * @param  ÎŞ
  * @retval ÎŞ
  */
void OLED_InitHard(void)
{
  OLED_ConfigGPIO();

  /* ÉÏµçÑÓ³Ù */
  OLEDDelay(0xfffff);
   /* Ä£¿é³§¼ÒÌá¹©³õÊ¼»¯´úÂë */
  OLED_WR_Byte(0xAE,OLED_CMD);	/* ¹Ø±ÕOLEDÃæ°åÏÔÊ¾(ĞİÃß) */
  OLED_WR_Byte(0x00,OLED_CMD);	/* ÉèÖÃÁĞµØÖ·µÍ4bit */
  OLED_WR_Byte(0x10,OLED_CMD);	/* ÉèÖÃÁĞµØÖ·¸ß4bit */
  OLED_WR_Byte(0x40,OLED_CMD);	/* ÉèÖÃÆğÊ¼ĞĞµØÖ·£¨µÍ5bit 0-63£©£¬ Ó²¼şÏà¹Ø*/

  OLED_WR_Byte(0x81,OLED_CMD);	/* ÉèÖÃ¶Ô±È¶ÈÃüÁî(Ë«×Ö½ÚÃüÁî£©£¬µÚ1¸ö×Ö½ÚÊÇÃüÁî£¬µÚ2¸ö×Ö½ÚÊÇ¶Ô±È¶È²ÎÊı0-255 */
  OLED_WR_Byte(0xCF,OLED_CMD);	/* ÉèÖÃ¶Ô±È¶È²ÎÊı */

  OLED_WR_Byte(0xA1,OLED_CMD);	/* A0 £ºÁĞµØÖ·0Ó³Éäµ½SEG0; A1 £ºÁĞµØÖ·127Ó³Éäµ½SEG0 */
  OLED_WR_Byte(0xA6,OLED_CMD);	/* A6 : ÉèÖÃÕı³£ÏÔÊ¾Ä£Ê½; A7 : ÉèÖÃÎª·´ÏÔÄ£Ê½ */

  OLED_WR_Byte(0xA8,OLED_CMD);	/* ÉèÖÃCOMÂ·Êı */
  OLED_WR_Byte(0x3F,OLED_CMD);	/* 1 ->£¨63+1£©Â· */

  OLED_WR_Byte(0xD3,OLED_CMD);	/* ÉèÖÃÏÔÊ¾Æ«ÒÆ£¨Ë«×Ö½ÚÃüÁî£©*/
  OLED_WR_Byte(0x00,OLED_CMD);	/* ÎŞÆ«ÒÆ */

  OLED_WR_Byte(0xD5,OLED_CMD);	/* ÉèÖÃÏÔÊ¾Ê±ÖÓ·ÖÆµÏµÊı/Õñµ´ÆµÂÊ */
  OLED_WR_Byte(0x80,OLED_CMD);	/* ÉèÖÃ·ÖÆµÏµÊı,¸ß4bitÊÇ·ÖÆµÏµÊı£¬µÍ4bitÊÇÕñµ´ÆµÂÊ */

  OLED_WR_Byte(0xD9,OLED_CMD);	/* ÉèÖÃÔ¤³äµçÖÜÆÚ */
  OLED_WR_Byte(0xF1,OLED_CMD);	/* [3:0],PHASE 1; [7:4],PHASE 2; */

  OLED_WR_Byte(0xDA,OLED_CMD);	/* ÉèÖÃCOM½ÅÓ²¼ş½ÓÏß·½Ê½ */
  OLED_WR_Byte(0x12,OLED_CMD);

  OLED_WR_Byte(0xDB,OLED_CMD);	/* ÉèÖÃ vcomh µçÑ¹±¶ÂÊ */
  OLED_WR_Byte(0x40,OLED_CMD);	/* [6:4] 000 = 0.65 x VCC; 0.77 x VCC (RESET); 0.83 x VCC  */

  OLED_WR_Byte(0x8D,OLED_CMD);	/* ÉèÖÃ³äµç±Ã£¨ºÍÏÂ¸öÃüÁî½áºÏÊ¹ÓÃ£© */
  OLED_WR_Byte(0x14,OLED_CMD);	/* 0x14 Ê¹ÄÜ³äµç±Ã£¬ 0x10 ÊÇ¹Ø±Õ */
  OLED_WR_Byte(0xAF,OLED_CMD);	/* ´ò¿ªOLEDÃæ°å */
}

 /**
  * @file   OLED_Init
  * @brief  ³õÊ¼»¯OLEDÆÁ
  * @param  ÎŞ
  * @retval ÎŞ
  */
void OLED_Init(void)
{
     OLED_InitHard();	 /* ³õÊ¼»¯OLEDÓ²¼ş */
     OLED_ClrScr(0x00);	 /* ÇåÆÁ£¬0x00±íÊ¾ºÚµ×£» 0xFF ±íÊ¾°×µ× */
    /* ÉèÖÃ×ÖÌå²ÎÊı */
    tFont16.usFontCode = FC_ST_16;	/* ×ÖÌå´úÂë 16µãÕó */
    tFont16.usTextColor = 1;		/* ×ÖÌåÑÕÉ« 0 »ò 1 */
    tFont16.usBackColor = 0;		/* ÎÄ×Ö±³¾°ÑÕÉ« 0 »ò 1 */
    tFont16.usSpace = 0;			/* ÎÄ×Ö¼ä¾à£¬µ¥Î» = ÏñËØ */

    tFont12.usFontCode = FC_ST_12;	/* ×ÖÌå´úÂë 12µãÕó */
    tFont12.usTextColor = 1;		/* ×ÖÌåÑÕÉ« 0 »ò 1 */
    tFont12.usBackColor = 0;		/* ÎÄ×Ö±³¾°ÑÕÉ« 0 »ò 1 */
    tFont12.usSpace = 1;			/* ÎÄ×Ö¼ä¾à£¬µ¥Î» = ÏñËØ */
}

 /**
  * @file   OLED_WR_Byte
  * @brief  ÏòOLED·¢ËÍÒ»×Ö½Ú
  * @param  dat:ÒªĞ´ÈëµÄÊı¾İ/ÃüÁî
  *         cmd:Êı¾İ/ÃüÁî±êÖ¾ 0,±íÊ¾ÃüÁî;1,±íÊ¾Êı¾İ;
  * @retval ÎŞ
  */
void OLED_WR_Byte(uint8_t dat,uint8_t cmd)
{
  uint8_t i;
  SSD_CS_0();
  SSD_SCK_0();
  if (cmd==1)/* 0 ±íÊ¾ºóÃæ´«ËÍµÄÊÇÃüÁî 1±íÊ¾ºóÃæ´«ËÍµÄÊı¾İ */
  {
    SSD_SDIN_1();//Êı¾İ
  }
  else
  {
    SSD_SDIN_0();//ÃüÁî
  }
//	SSD_SDIN_0();	/* 0 ±íÊ¾ºóÃæ´«ËÍµÄÊÇÃüÁî,1±íÊ¾ºóÃæ´«ËÍµÄÊı¾İ */
  SSD_SCK_1();
  for (i = 0; i < 8; i++)
  {
    if (dat & 0x80)
    {
			SSD_SDIN_1();
    }
    else
    {
			SSD_SDIN_0();
    }
    SSD_SCK_0();
    dat <<= 1;
    SSD_SCK_1();
  }
  SSD_CS_1();
}	

 /**
  * @file   OLED_DispOn
  * @brief  ´ò¿ªÏÔÊ¾
  * @param  ÎŞ
  * @retval ÎŞ
  */
void OLED_DispOn(void)
{
  OLED_WR_Byte(0X8D,OLED_CMD); 	/* ÉèÖÃ³äµç±Ã£¨ºÍÏÂ¸öÃüÁî½áºÏÊ¹ÓÃ£© */
  OLED_WR_Byte(0X14,OLED_CMD);	/* 0x14 Ê¹ÄÜ³äµç±Ã£¬ 0x10 ÊÇ¹Ø±Õ */
  OLED_WR_Byte(0XAF,OLED_CMD);	/* ´ò¿ªOLEDÃæ°å */
}
 /**
  * @file   OLED_DispOff
  * @brief  ¹Ø±ÕÏÔÊ¾
  * @param  ÎŞ
  * @retval ÎŞ
  */
void OLED_DispOff(void)
{
  OLED_WR_Byte(0X8D,OLED_CMD);	/* ÉèÖÃ³äµç±Ã£¨ºÍÏÂ¸öÃüÁî½áºÏÊ¹ÓÃ£©*/
  OLED_WR_Byte(0X10,OLED_CMD);	/* 0x14 Ê¹ÄÜ³äµç±Ã£¬0x10 ÊÇ¹Ø±Õ */
  OLED_WR_Byte(0XAE,OLED_CMD);	/* ´ò¿ªOLEDÃæ°å */
}
 /**
  * @file   OLED_StartDraw
  * @brief  ¿ªÊ¼»æÍ¼¡£ÒÔºó»æÍ¼º¯ÊıÖ»¸ÄĞ´»º³åÇø£¬²»¸ÄĞ´Ãæ°åÏÔ´æ
  * @param  ÎŞ
  * @retval ÎŞ
  */
void OLED_StartDraw(void)
{
  s_ucUpdateEn = 0;
}

 /**
  * @file   OLED_EndDraw
  * @brief  ½áÊø»æÍ¼¡£»º³åÇøµÄÊı¾İË¢ĞÂµ½Ãæ°åÏÔ´æ¡£ OLED_StartDraw() ºÍ OLED_EndDraw() ±ØĞë³É¶ÔÊ¹ÓÃ
  * @param  ÎŞ
  * @retval ÎŞ
  */
void OLED_EndDraw(void)
{
  s_ucUpdateEn = 1;
  OLED_BufToPanel();
}


 /**
  * @file   OLED_ClrScr
  * @brief  ÇåÆÁ
  * @param  ucMode : 0 ±íÊ¾È«ºÚ£» 0xFF±íÊ¾È«ÁÁ
  * @retval ÎŞ
  */
void OLED_ClrScr(uint8_t _ucMode)
{
  uint8_t i,j;

  for (i = 0 ; i < 8; i++)
  {
    for (j = 0 ; j < 128; j++)
    {
			s_ucGRAM[i][j] = _ucMode;
    }
  }

  if (s_ucUpdateEn == 1)
  {
    OLED_BufToPanel();
  }
}

 /**
  * @file   OLED_BufToPanel
  * @brief  ½«»º³åÇøÖĞµÄµãÕóÊı¾İĞ´ÈëÃæ°å
  * @param  ÎŞ
  * @retval ÎŞ
  */
static void OLED_BufToPanel(void)
{
  uint8_t i,j;

  for (i = 0 ; i< 8; i++)
  {
    //OLED_WR_Byte(0X8D,OLED_CMD); 
    OLED_WR_Byte ((0xB0 + i),OLED_CMD);	/* ÉèÖÃÒ³µØÖ·£¨0~7£© */
    OLED_WR_Byte (0x00,OLED_CMD);		/* ÉèÖÃÁĞµØÖ·µÄµÍµØÖ· */
    OLED_WR_Byte (0x10,OLED_CMD);		/* ÉèÖÃÁĞµØÖ·µÄ¸ßµØÖ· */
    for (j = 0 ; j < 128; j++)
    {
      OLED_WR_Byte(s_ucGRAM[i][j],OLED_DATA);
    }
  }
}


 /**
  * @file   OLED_DispStr
  * @brief  ÔÚÆÁÄ»Ö¸¶¨×ø±ê£¨×óÉÏ½ÇÎª0£¬0£©ÏÔÊ¾Ò»¸ö×Ö·û´®
  * @param 
	*		_usX : X×ø±ê£¬¶ÔÓÚ12864ÆÁ£¬·¶Î§Îª¡¾0 - 127¡¿
	*		_usY : Y×ø±ê£¬¶ÔÓÚ12864ÆÁ£¬·¶Î§Îª¡¾0 - 63¡¿
	*		_ptr  : ×Ö·û´®Ö¸Õë
	*		_tFont : ×ÖÌå½á¹¹Ìå£¬°üº¬ÑÕÉ«¡¢±³¾°É«(Ö§³ÖÍ¸Ã÷)¡¢×ÖÌå´úÂë¡¢ÎÄ×Ö¼ä¾àµÈ²ÎÊı
  * @retval ÎŞ
  */
void OLED_DispStr(uint16_t _usX, uint16_t _usY, char *_ptr, FONT_T *_tFont)
{
  uint32_t i;
  uint8_t code1;
  uint8_t code2;
  uint32_t address;
  uint8_t buf[24 * 24 / 8];	/* ×î´óÖ§³Ö24µãÕóºº×Ö */
  uint8_t m, width;
  uint8_t font_width,font_height, font_bytes;
  uint16_t x, y;
  const uint8_t *pAscDot;
  const uint8_t *pHzDot;

  /* Èç¹û×ÖÌå½á¹¹Îª¿ÕÖ¸Õë£¬ÔòÈ±Ê¡°´16µãÕó */	
  if (_tFont->usFontCode == FC_ST_12)
	{
			font_height = 12;
			font_width = 12;
			font_bytes = 24;
			pAscDot = g_Ascii12;
			pHzDot = g_Hz12;
  }
  else
  {
		/* È±Ê¡ÊÇ16µãÕó */
		font_height = 16;
		font_width = 16;
		font_bytes = 32;
		pAscDot = g_Ascii16;
		pHzDot = g_Hz16;
  }

  /* ¿ªÊ¼Ñ­»·´¦Àí×Ö·û */
  while (*_ptr != 0)
  {
      code1 = *_ptr;	/* ¶ÁÈ¡×Ö·û´®Êı¾İ£¬ ¸ÃÊı¾İ¿ÉÄÜÊÇascii´úÂë£¬Ò²¿ÉÄÜºº×Ö´úÂëµÄ¸ß×Ö½Ú */
      if (code1 < 0x80)
      {
                /* ½«ascii×Ö·ûµãÕó¸´ÖÆµ½buf */
					memcpy(buf, &pAscDot[code1 * (font_bytes / 2)], (font_bytes / 2));
					width = font_width / 2;
      }
      else
      {
        code2 = *++_ptr;
        if (code2 == 0)
        {
						break;
        }

        /* ¼ÆËã16µãÕóºº×ÖµãÕóµØÖ·
                  ADDRESS = [(code1-0xa1) * 94 + (code2-0xa1)] * 32
                  ;
        */
        #ifdef USE_SMALL_FONT
        m = 0;
        while(1)
        {         
          address = m * (font_bytes + 2);
          m++;
          if ((code1 == pHzDot[address + 0]) && (code2 == pHzDot[address + 1]))
          {
						address += 2;
						memcpy(buf, &pHzDot[address], font_bytes);
						break;
          }
          else if ((pHzDot[address + 0] == 0xFF) && (pHzDot[address + 1] == 0xFF))
          {
								/* ×Ö¿âËÑË÷Íê±Ï£¬Î´ÕÒµ½£¬ÔòÌî³äÈ«FF */
						memset(buf, 0xFF, font_bytes);
						break;
          }
        }
        #else	/* ÓÃÈ«×Ö¿â */
          /* ´Ë´¦ĞèÒª¸ù¾İ×Ö¿âÎÄ¼ş´æ·ÅÎ»ÖÃ½øĞĞĞŞ¸Ä */
          address = ((code1-0xa1) * 94 + (code2-0xa1)) * font_bytes + HZK16_ADDR;
          memcpy(buf, (const uint8_t *)address, font_bytes);
        #endif

        width = font_width;
      }

    y = _usY;
    /* ¿ªÊ¼Ë¢LCD */
    for (m = 0; m < font_height; m++)	/* ×Ö·û¸ß¶È */
    {
      x = _usX;															 
      for (i = 0; i < width; i++)	/* ×Ö·û¿í¶È */
      {
          if ((buf[m * ((2 * width) / font_width) + i / 8] & (0x80 >> (i % 8 ))) != 0x00)
          {
                    OLED_PutPixel(x, y, _tFont->usTextColor);	/* ÉèÖÃÏñËØÑÕÉ«ÎªÎÄ×ÖÉ« */
          }
          else
          {
                    OLED_PutPixel(x, y, _tFont->usBackColor);	/* ÉèÖÃÏñËØÑÕÉ«ÎªÎÄ×Ö±³¾°É« */
          }

          x++;
      }
      y++;
    }

    if (_tFont->usSpace > 0)
    {
    /* Èç¹ûÎÄ×Öµ×É«°´_tFont->usBackColor£¬²¢ÇÒ×Ö¼ä¾à´óÓÚµãÕóµÄ¿í¶È£¬ÄÇÃ´ĞèÒªÔÚÎÄ×ÖÖ®¼äÌî³ä(ÔİÊ±Î´ÊµÏÖ) */
    }
    _usX += width + _tFont->usSpace;	/* ÁĞµØÖ·µİÔö */
    _ptr++;			/* Ö¸ÏòÏÂÒ»¸ö×Ö·û */
  }
}

 /**
  * @file  OLED_PutPixel
  * @brief  »­1¸öÏñËØ
  * @param  
	*			_usX,_usY : ÏñËØ×ø±ê
	*			_ucColor  £ºÏñËØÑÕÉ«
  * @retval ÎŞ
  */
void OLED_PutPixel(uint16_t _usX, uint16_t _usY, uint8_t _ucColor)
{
  uint8_t ucValue;
  uint8_t ucPageAddr;
  uint8_t ucColAddr;
  #ifdef TRUN_180_EN
  const uint8_t aOrTab[8]  = {0x01, 0x02, 0x04, 0x08,0x10,0x20,0x40,0x80};
  const uint8_t aAndTab[8] = {0xFE, 0xFD, 0xFB, 0xF7,0xEF,0xDF,0xBF,0x7F};

  ucPageAddr = _usY / 8;
  ucColAddr = 127 - _usX;
  #else
  const uint8_t aOrTab[8]  = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};
  const uint8_t aAndTab[8] = {0x7F, 0xBF, 0xDF, 0xEF, 0xF7, 0xFB, 0xFD, 0xFE};

  ucPageAddr = 7 - _usY / 8;
  ucColAddr = _usX;
  #endif

  ucValue = s_ucGRAM[ucPageAddr][ucColAddr];
  if (_ucColor == 0)
  {
    ucValue &= aAndTab[_usY % 8];
  }
  else
  {
    ucValue |= aOrTab[_usY % 8];
  }
  s_ucGRAM[ucPageAddr][ucColAddr] = ucValue;

  if (s_ucUpdateEn == 1)
  {
    OLED_WR_Byte (0xB0 + ucPageAddr,OLED_CMD);					/* ÉèÖÃÒ³µØÖ·£¨0~7£© */
    OLED_WR_Byte (0x00 + (ucColAddr & 0x0F),OLED_CMD);			/* ÉèÖÃÁĞµØÖ·µÄµÍµØÖ· */
    OLED_WR_Byte (0x10 + ((ucColAddr >> 4) & 0x0F),OLED_CMD);	/* ÉèÖÃÁĞµØÖ·µÄ¸ßµØÖ· */
    OLED_WR_Byte(ucValue,OLED_DATA);
  }
}

 /**
  * @file   OLED_GetPixel
  * @brief ¶ÁÈ¡1¸öÏñËØ
  * @param  _usX,_usY : ÏñËØ×ø±ê
  * @retval ÑÕÉ«Öµ (0, 1)
  */
uint8_t OLED_GetPixel(uint16_t _usX, uint16_t _usY)
  {
  uint8_t ucValue;
  uint8_t ucPageAddr;
  uint8_t ucColAddr;
  #ifdef TRUN_180_EN
  ucPageAddr = _usY / 8;
  ucColAddr = 127 - _usX;
  #else
  ucPageAddr = 7 - _usY / 8;
  ucColAddr = _usX;
  #endif

  ucValue = s_ucGRAM[ucPageAddr][ucColAddr];
  if (ucValue & (_usY % 8))
  {
    return 1;
  }
  else
  {
    return 0;
  }
}


 /**
  * @file  OLED_DrawLine
  * @brief ²ÉÓÃ Bresenham Ëã·¨£¬ÔÚ2µã¼ä»­Ò»ÌõÖ±Ïß¡£
  * @param 
	*					_usX1, _usY1 £ºÆğÊ¼µã×ø±ê
	*					_usX2, _usY2 £ºÖÕÖ¹µãY×ø±ê
	*					_ucColor     £ºÑÕÉ«
  * @retval ÎŞ
  */
void OLED_DrawLine(uint16_t _usX1 , uint16_t _usY1 , uint16_t _usX2 , uint16_t _usY2 , uint8_t _ucColor)
{
  int32_t dx , dy ;
  int32_t tx , ty ;
  int32_t inc1 , inc2 ;
  int32_t d , iTag ;
  int32_t x , y ;

  /* ²ÉÓÃ Bresenham Ëã·¨£¬ÔÚ2µã¼ä»­Ò»ÌõÖ±Ïß */

  OLED_PutPixel(_usX1 , _usY1 , _ucColor);

  /* Èç¹ûÁ½µãÖØºÏ£¬½áÊøºóÃæµÄ¶¯×÷¡£*/
  if ( _usX1 == _usX2 && _usY1 == _usY2 )
  {
    return;
  }

  iTag = 0 ;
  /* dx = abs ( _usX2 - _usX1 ); */
  if (_usX2 >= _usX1)
  {
      dx = _usX2 - _usX1;
  }
  else
  {
      dx = _usX1 - _usX2;
  }

  /* dy = abs ( _usY2 - _usY1 ); */
  if (_usY2 >= _usY1)
  {
      dy = _usY2 - _usY1;
  }
  else
  {
      dy = _usY1 - _usY2;
  }

  if ( dx < dy )   /*Èç¹ûdyÎª¼Æ³¤·½Ïò£¬Ôò½»»»×İºá×ø±ê¡£*/
  {
      uint16_t temp;

      iTag = 1 ;
      temp = _usX1; _usX1 = _usY1; _usY1 = temp;
      temp = _usX2; _usX2 = _usY2; _usY2 = temp;
      temp = dx; dx = dy; dy = temp;
  }
  tx = _usX2 > _usX1 ? 1 : -1 ;    /* È·¶¨ÊÇÔö1»¹ÊÇ¼õ1 */
  ty = _usY2 > _usY1 ? 1 : -1 ;
  x = _usX1 ;
  y = _usY1 ;
  inc1 = 2 * dy ;
  inc2 = 2 * ( dy - dx );
  d = inc1 - dx ;
  while ( x != _usX2 )     /* Ñ­»·»­µã */
  {
      if ( d < 0 )
      {
        d += inc1 ;
      }
      else
      {
        y += ty ;
        d += inc2 ;
      }
      if ( iTag )
      {
        OLED_PutPixel ( y , x , _ucColor) ;
      }
      else
      {
        OLED_PutPixel ( x , y , _ucColor) ;
      }
      x += tx ;
  }
}

 /**
  * @file  OLED_DrawPoints
  * @brief ²ÉÓÃ Bresenham Ëã·¨£¬»æÖÆÒ»×éµã£¬²¢½«ÕâĞ©µãÁ¬½ÓÆğÀ´¡£¿ÉÓÃÓÚ²¨ĞÎÏÔÊ¾¡£
  * @param 
	*             x, y     £º×ø±êÊı×é
	*	   	      	_ucColor £ºÑÕÉ«
  * @retval ÎŞ
  */
void OLED_DrawPoints(uint16_t *x, uint16_t *y, uint16_t _usSize, uint8_t _ucColor)
{
    uint16_t i;

    for (i = 0 ; i < _usSize - 1; i++)
    {
      OLED_DrawLine(x[i], y[i], x[i + 1], y[i + 1], _ucColor);
    }
}

 /**
  * @file  OLED_DrawRect
  * @brief »æÖÆ¾ØĞÎ¡£
  * @param 
	*			    _usX,_usY£º¾ØĞÎ×óÉÏ½ÇµÄ×ø±ê
	*			    _usHeight £º¾ØĞÎµÄ¸ß¶È
	*			    _usWidth  £º¾ØĞÎµÄ¿í¶È
  * @retval ÎŞ
  */
void OLED_DrawRect(uint16_t _usX, uint16_t _usY, uint8_t _usHeight, uint16_t _usWidth, uint8_t _ucColor)
{
    /*
     ---------------->---
    |(_usX£¬_usY)        |
    V                    V  _usHeight
    |                    |
     ---------------->---
                _usWidth
    */

    OLED_DrawLine(_usX, _usY, _usX + _usWidth - 1, _usY, _ucColor);	/* ¶¥ */
    OLED_DrawLine(_usX, _usY + _usHeight - 1, _usX + _usWidth - 1, _usY + _usHeight - 1, _ucColor);	/* µ× */

    OLED_DrawLine(_usX, _usY, _usX, _usY + _usHeight - 1, _ucColor);	/* ×ó */
    OLED_DrawLine(_usX + _usWidth - 1, _usY, _usX + _usWidth - 1, _usY + _usHeight, _ucColor);	/* ÓÒ */
}

 /**
  * @file  OLED_DrawCircle
  * @brief »æÖÆÒ»¸öÔ²£¬±Ê¿íÎª1¸öÏñËØ
  * @param 
	*			_usX,_usY  £ºÔ²ĞÄµÄ×ø±ê
	*			_usRadius  £ºÔ²µÄ°ë¾¶
  * @retval ÎŞ
  */
void OLED_DrawCircle(uint16_t _usX, uint16_t _usY, uint16_t _usRadius, uint8_t _ucColor)
{
  int32_t  D;			/* Decision Variable */
  uint32_t  CurX;		/* µ±Ç° X Öµ */
  uint32_t  CurY;		/* µ±Ç° Y Öµ */

  D = 3 - (_usRadius << 1);
  CurX = 0;
  CurY = _usRadius;

  while (CurX <= CurY)
  {
      OLED_PutPixel(_usX + CurX, _usY + CurY, _ucColor);
      OLED_PutPixel(_usX + CurX, _usY - CurY, _ucColor);
      OLED_PutPixel(_usX - CurX, _usY + CurY, _ucColor);
      OLED_PutPixel(_usX - CurX, _usY - CurY, _ucColor);
      OLED_PutPixel(_usX + CurY, _usY + CurX, _ucColor);
      OLED_PutPixel(_usX + CurY, _usY - CurX, _ucColor);
      OLED_PutPixel(_usX - CurY, _usY + CurX, _ucColor);
      OLED_PutPixel(_usX - CurY, _usY - CurX, _ucColor);

      if (D < 0)
      {
        D += (CurX << 2) + 6;
      }
      else
      {
        D += ((CurX - CurY) << 2) + 10;
        CurY--;
      }
      CurX++;
  }
}

 /**
  * @file  OLED_DrawBMP
  * @brief ÔÚLCDÉÏÏÔÊ¾Ò»¸öBMPÎ»Í¼£¬Î»Í¼µãÕóÉ¨Ãè´ÎĞò£º´Ó×óµ½ÓÒ£¬´ÓÉÏµ½ÏÂ
  * @param 
	*			_usX, _usY : Í¼Æ¬µÄ×ø±ê
	*			_usHeight  £ºÍ¼Æ¬¸ß¶È
	*			_usWidth   £ºÍ¼Æ¬¿í¶È
	*			_ptr       £ºµ¥É«Í¼Æ¬µãÕóÖ¸Õë£¬Ã¿¸öÏñËØÕ¼ÓÃ1¸ö×Ö½Ú
  * @retval ÎŞ
  */
void OLED_DrawBMP(uint16_t _usX, uint16_t _usY, uint16_t _usHeight, uint16_t _usWidth, uint8_t *_ptr)
{
  uint16_t x, y;

  for (x = 0; x < _usWidth; x++)
  {
      for (y = 0; y < _usHeight; y++)
      {
          OLED_PutPixel(_usX + x, _usY + y, *_ptr);
      }
  }
}
 /**
  * @file  OLED_DisDigital
  * @brief ÔÚÆÁÄ»Ö¸¶¨×ø±ê£¨×óÉÏ½ÇÎª0£¬0£©ÏÔÊ¾Ò»¸öÕûÊı¡£
  * @param 
	*		_usX : X×ø±ê£¬¶ÔÓÚ12864ÆÁ£¬·¶Î§Îª¡¾0 - 127¡¿
	*		_usY : Y×ø±ê£¬¶ÔÓÚ12864ÆÁ£¬·¶Î§Îª¡¾0 - 63¡¿
	*		Dig_Data  : Ê®½øÖÆÕûÊı
	*		_tFont : ×ÖÌå½á¹¹Ìå£¬°üº¬ÑÕÉ«¡¢±³¾°É«(Ö§³ÖÍ¸Ã÷)¡¢×ÖÌå´úÂë¡¢ÎÄ×Ö¼ä¾àµÈ²ÎÊıÚ
  * @retval ÎŞ
  */
void OLED_DisDigital(uint16_t _usX, uint16_t _usY, uint32_t Dig_Data, FONT_T *_tFont)
{
  char dd[11];
  uint8_t i,j=9;
  uint32_t temp;
  temp = Dig_Data;
  dd[10]=0;
  for(i=10;(i>j)&(i>0);i--) 
   { 
     dd[i-1] = temp%10 + '0';
     temp=temp/10;
     if(temp) j--; 
   }
  OLED_DispStr(_usX, _usY,&dd[i],&(*_tFont));
}
 /**
  * @file  oled_pow
  * @brief  mµÄn´Î·½
  * @param 
	*		    m : 
	*		    n :
  * @retval ÓĞ
  */
uint32_t oled_pow(uint8_t m,uint8_t n)
{
  uint32_t result=1;	 
  while(n--)result*=m;    
  return result;
}	

 /**
  * @file  OLED_DisDecimal
  * @brief  ÔÚÆÁÄ»Ö¸¶¨×ø±ê£¨×óÉÏ½ÇÎª0£¬0£©ÏÔÊ¾Ò»¸öĞ¡Êı£¬ÕûÊıºÍĞ¡Êı²¿·Ö×î¶à¾ÅÎ»¡£
  * @param 
	*		_usX : X×ø±ê£¬¶ÔÓÚ12864ÆÁ£¬·¶Î§Îª¡¾0 - 127¡¿
	*		_usY : Y×ø±ê£¬¶ÔÓÚ12864ÆÁ£¬·¶Î§Îª¡¾0 - 63¡¿
	*		Dig_Data  : Ğ¡Êı
	*   DecimalNum: Ğ¡Êı¸öÊı
	*		_tFont : ×ÖÌå½á¹¹Ìå£¬°üº¬ÑÕÉ«¡¢±³¾°É«(Ö§³ÖÍ¸Ã÷)¡¢×ÖÌå´úÂë¡¢ÎÄ×Ö¼ä¾àµÈ²ÎÊı
  * @retval ÎŞ
  */
void OLED_DisDecimal(uint16_t _usX, uint16_t _usY, double Dig_Data,uint8_t DecimalNum, FONT_T *_tFont)
{
  int NumTemp;
  char dd[11];
  uint8_t i,j=9;
  int temp;
  NumTemp=(uint32_t)Dig_Data;
  temp =(int)((Dig_Data-(double)NumTemp)*oled_pow(10,DecimalNum));
  dd[10]=0;
  for(i=0;i<DecimalNum;i++)
  {
    dd[9-i]=0 + '0';//Ğ¡Êı¸³³õÊ¼Öµ0
  }
  for(i=10;(i>j)&(i>0);i--) 
  {    
    dd[i-1] = temp%10 + '0';
    temp=temp/10; 
    if(temp) 
    {
      j--;
    }				 
  } 
  dd[9-DecimalNum]='.';
  i=9-DecimalNum;
  j=9-DecimalNum-1;
  temp =(uint32_t)Dig_Data;//ÇóÕûÊı²¿·Ö
  for(;(i>j)&(i>0);i--) //12345
  { 
    dd[i-1] = temp%10 + '0';//i=7
    temp=temp/10;// 333 33 3  i=10 9 8 j=9 8 7  
    if(temp) 
    {
      j--;
    }				 
  }
  OLED_DispStr(_usX, _usY,&dd[i],&(*_tFont));
}






