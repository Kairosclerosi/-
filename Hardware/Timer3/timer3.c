#include "timer3.h"

void vTIM3_Init(uint32_t ulPeriodInMs)			   //��ʱ��3��ʼ��
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;					
	NVIC_InitTypeDef NVIC_InitStructure;							

	/* ʹ�ܶ�ʱ��3��ʱ�� */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); 			

	/* ��ʼ����ʱ��3��ʱ�� */
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;										/* ��Ƶֵ0 */
	TIM_TimeBaseStructure.TIM_Prescaler = 71;												/* Ԥ��Ƶֵ */
	TIM_TimeBaseStructure.TIM_Period = (uint16_t)(ulPeriodInMs - 1);               
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   	/* ���ϼ���ģʽ */
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

	/* ʹ�ܶ�ʱ���ĸ����ж� */
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
	
	/* ���ö�ʱ��3�����жϵ�NVIC */
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  					
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = TIM3_PreemptionPriority; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = TIM3_SubPriority;  			
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 				
	NVIC_Init(&NVIC_InitStructure);  							
	
	/* ʹ�ܶ�ʱ��3 */
	TIM_Cmd(TIM3, ENABLE);  																				 
}

/* end of file cppyright reserve by team of yanjun ,More information please browse www.yanjuntech.cn */
