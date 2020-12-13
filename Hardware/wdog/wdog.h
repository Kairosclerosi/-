#ifndef _WDOG_H
#define _WDOG_H

#include "system.h"

#define IWDG_PERIOD_4000MS		((uint32_t)2500)
#define IWDG_PERIOD_2000MS		((uint32_t)1250)

void vIWDG_Init(uint32_t ucReloadTimeInMs);
void vIWDG_Feed(void);

#endif
