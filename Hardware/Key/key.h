#ifndef __KEY_H
#define __KEY_H

#include "systick.h"
#include "system.h"

#define KEY2 PCin(13)	//¶ÁÈ¡°´¼ü 2

#define KEY2_PORT 			GPIOD
#define KEY2_GPIO_PIN 	GPIO_Pin_7
#define KEY2_RCC				RCC_APB2Periph_GPIOD

extern uint8_t ucKeyIdFlag;
extern uint32_t ui_KeyCount;
void vKEY_Init(void);
void vKEY_Scan(void);
void vKEY_Driver(void);

#endif


