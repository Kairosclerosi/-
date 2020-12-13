#ifndef _SYSTICK_H
#define _SYSTICK_H

#include "stm32f10x.h"

void vSystickDelayInit(void);
void vSystickDelayMs(uint32_t ulNms);
void vSystickDelayUs(uint32_t ulNus);
void vSystickDelayS(uint32_t ulNs);

#endif
