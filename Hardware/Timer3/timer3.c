#include "timer3.h"

void vTIM3_Init(uint32_t ulPeriodInMs)			   //定时器3初始化
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;					
	NVIC_InitTypeDef NVIC_InitStructure;							

	/* 使能定时器3的时钟 */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); 			

	/* 初始化定时器3的时基 */
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;										/* 分频值0 */
	TIM_TimeBaseStructure.TIM_Prescaler = 71;												/* 预分频值 */
	TIM_TimeBaseStructure.TIM_Period = (uint16_t)(ulPeriodInMs - 1);               
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   	/* 向上计数模式 */
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

	/* 使能定时器的更新中断 */
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
	
	/* 配置定时器3更新中断的NVIC */
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  					
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = TIM3_PreemptionPriority; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = TIM3_SubPriority;  			
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 				
	NVIC_Init(&NVIC_InitStructure);  							
	
	/* 使能定时器3 */
	TIM_Cmd(TIM3, ENABLE);  																				 
}

/* end of file cppyright reserve by team of yanjun ,More information please browse www.yanjuntech.cn */
