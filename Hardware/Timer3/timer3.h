#ifndef _TIMER3_H
#define _TIMER3_H

#include "system.h"

#define TIMER3_CALLBACK_FREQUENCY_1000HZ		((uint16_t)1000)

/* 定时器3中断优先级，应该放在system.h文件中 */
#define TIM3_PreemptionPriority									(0X00)
#define TIM3_SubPriority												(0X00)

void vTIM3_Init(uint32_t ulPeriodInMs);

#endif

/* end of file cppyright reserve by team of yanjun ,More information please browse www.yanjuntech.cn */
