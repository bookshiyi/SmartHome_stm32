#ifndef _HAL_INFRARED_H
#define _HAL_INFRARED_H
#include "stdbool.h"

#define Infrared_GPIO_Port         GPIOB
#define Infrared_GPIO_Pin          GPIO_PIN_4
//#define Infrared_EXTI_LineX        EXTI_Line7

void irInit(void);
bool irRead(void);

#endif /*_HAL_INFRARED_H*/


