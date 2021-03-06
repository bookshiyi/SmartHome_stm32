/*
*********************************************************************************************************
*
*	模块名称 : 汉字点阵字库。有效显示区 高11x宽11, 最右一列留白
*	文件名称 : hz12.c
*	版    本 : V1.0
*	说    明 : 只包含本程序用到汉字字库
*	修改记录 :
*		版本号  日期       作者    说明
*		v1.0    2011-09-08 armfly  ST固件库V3.5.0版本。
*
*	Copyright (C), 2010-2011, 安富莱电子 www.armfly.com
*
*********************************************************************************************************
*/


/*
	FLASH中内嵌小字库，只包括本程序用到的汉字点阵
	每行点阵数据，头2字节是汉子的内码，后面32字节是16点阵汉子的字模数据。
*/

unsigned char const g_Hz12[] = {
0xB4,0xFD, 0x11,0x00,0x21,0x40,0x47,0xE0,0x11,0x00,0x2F,0xF0,0x60,0x40,0xAF,0xF0,0x20,0x40,// 待 //
           0x24,0x40,0x24,0x40,0x21,0x40,0x20,0x80,

0xB6,0xD3, 0x01,0x00,0x79,0x00,0x49,0x00,0x51,0x00,0x61,0x00,0x51,0x00,0x4A,0x80,0x6A,0x80,// 队 //
           0x54,0x40,0x44,0x40,0x48,0x20,0x50,0x10,

0xBA,0xC5, 0x3F,0xC0,0x20,0x40,0x20,0x40,0x3F,0xC0,0x00,0x20,0xFF,0xF0,0x08,0x00,0x1F,0xC0,// 号 //
           0x00,0x40,0x00,0x80,0x04,0x80,0x03,0x00,

0xBB,0xA7, 0x04,0x00,0x02,0x20,0x3F,0xF0,0x20,0x20,0x20,0x20,0x3F,0xE0,0x20,0x00,0x20,0x00,// 户 //
           0x20,0x00,0x20,0x00,0x40,0x00,0x80,0x00,

0xBD,0xD3, 0x21,0x00,0x20,0x80,0x27,0xE0,0xF2,0x40,0x2F,0xF0,0x31,0x00,0xE2,0x20,0x2F,0xF0,// 接 //
           0x24,0x40,0x23,0x80,0xA6,0x60,0x58,0x10,

0xBF,0xCD, 0x04,0x00,0x7F,0xF0,0x48,0x10,0x8F,0xA0,0x19,0x00,0x26,0x00,0x09,0x80,0x30,0x70,// 客 //
           0xDF,0x80,0x10,0x80,0x10,0x80,0x1F,0x80,

0xC3,0xBB, 0x40,0x80,0x27,0xC0,0x04,0x80,0x84,0xF0,0x48,0x00,0x27,0xC0,0x24,0x40,0xC2,0x80,// 没 //
           0x41,0x00,0x42,0x80,0x44,0x70,0x58,0x20,

0xC5,0xC5, 0x22,0x80,0x22,0x80,0x2E,0xF0,0xF2,0x80,0x22,0x80,0x3E,0xF0,0xE2,0x80,0x22,0x80,// 排 //
           0x2E,0xF0,0x22,0x80,0xA2,0x80,0x62,0x80,

0xC8,0xCB, 0x04,0x00,0x04,0x00,0x04,0x00,0x04,0x00,0x04,0x00,0x06,0x00,0x0A,0x00,0x09,0x00,// 人 //
           0x10,0x80,0x20,0x40,0x40,0x30,0x80,0x20,

0xCA,0xB1, 0x00,0x40,0x00,0x40,0xF8,0x40,0x8F,0xF0,0x88,0x40,0xFA,0x40,0x89,0x40,0x89,0x40,// 时 //
           0xF8,0x40,0x88,0x40,0x01,0x40,0x00,0xC0,

0xCE,0xDE, 0x00,0x40,0x7F,0xE0,0x04,0x00,0x04,0x00,0x04,0x20,0xFF,0xF0,0x05,0x00,0x05,0x00,// 无 //
           0x09,0x10,0x11,0x10,0x21,0x10,0xC0,0xF0,

0xD3,0xD0, 0x04,0x00,0x04,0x20,0xFF,0xF0,0x08,0x00,0x1F,0xC0,0x30,0x40,0x5F,0xC0,0x90,0x40,// 有 //
           0x1F,0xC0,0x10,0x40,0x11,0x40,0x10,0x80,

0xD4,0xDD, 0x10,0x30,0xFD,0xC0,0x51,0x00,0x7D,0xF0,0x11,0x40,0xFD,0x40,0x12,0x00,0x3F,0xC0,// 暂 //
           0x20,0x40,0x3F,0xC0,0x20,0x40,0x3F,0xC0,

0xD5,0xFD, 0x00,0x20,0x7F,0xF0,0x02,0x00,0x02,0x00,0x22,0x40,0x23,0xE0,0x22,0x00,0x22,0x00,// 正 //
           0x22,0x00,0x22,0x00,0x22,0x20,0xFF,0xF0,





/* 最后一行必须用0xFF,0xFF结束，这是字库数组结束标志 */
0xFF,0xFF

};
