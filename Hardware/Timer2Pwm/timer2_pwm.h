#ifndef _TIMER2_PWM_H
#define _TIMER2_PWM_H

#include "system.h"
#include "systick.h"

#define TIM2_PWM_PERIOD_20MS 				((int32_t)20)

#define	RCC_APBPeriph_TIMx_GPIOx	RCC_APB2Periph_GPIOA
#define	RCC_APBPeriph_TIMx	RCC_APB1Periph_TIM2
#define	TIM_GPIO	GPIOA
#define TIM_SERVO	TIM2

/* 留一定的死区 */
#define TIM2_MIN_PWM_PAUSE					((int32_t)0)
#define TIM2_MAX_PWM_PAUSE					((int32_t)1000)

void vTIM2_PwmInit(uint32_t ulClockDivide,uint16_t usPeriodTime);
void vTIM2_UnlockMoto(void);
void vTIM2_PwmOut(int32_t lChannel1, int32_t lChannel2, int32_t lChannel3, int32_t lChannel4);

#endif
