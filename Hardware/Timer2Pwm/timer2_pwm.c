#include "timer2_pwm.h"					//��ʱ��2PWM����������

void vTIM2_PwmInit(uint32_t ulClockDivide,uint16_t usPeriodTime)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;      
	 GPIO_InitTypeDef GPIO_InitStructure;

  /* TIM2 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
  /* GPIOA clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
  /* GPIOA Configuration:TIM2 Channel1, 2, 2 and 4 as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 |GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;                                       
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/* �����Զ���װ�ؼĴ������ڵ�ֵ */
	TIM_TimeBaseStructure.TIM_Period = (uint16_t)(((uint32_t)usPeriodTime) - 1);                       
	/* ����ʱ��Ƶ�ʳ�����Ԥ��Ƶֵ */
	TIM_TimeBaseStructure.TIM_Prescaler = (ulClockDivide - 1);                    
	/* ���ⲿʱ�ӽ��в�����ʱ�ӷ�Ƶ,����û���õ� */
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	/* ���ϼ���ģʽ */
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

	/**
	* PWM1 Mode configuration: Channel1
	* PWMģʽ1�� �����ϼ���ʱ��һ��TIMx_CNT<TIMx_CCR1ʱͨ��1Ϊ��Ч��ƽ������Ϊ
	* ��Ч��ƽ�������¼���ʱ��һ��TIMx_CNT>TIMx_CCR1ʱͨ��1Ϊ��Ч��ƽ(OC1REF=0)����
	* ��Ϊ��Ч��ƽ(OC1REF=1)��
	*/
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 
	/* ����Ƚ�ʹ�� */
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
	TIM_OCInitStructure.TIM_Pulse = 0;
	/* �������:TIM����Ƚϼ��� */
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 
	/* ����Tָ���Ĳ�����ʼ������TIM2 OC1 */
	TIM_OC1Init(TIM2, &TIM_OCInitStructure);  
	/* ʹ��TIM2��CCR1�ϵ�Ԥװ�ؼĴ��� */
	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);             

	/* PWM1 Mode configuration: Channel2 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 
	/* ʹ������Ƚ� */
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
	TIM_OCInitStructure.TIM_Pulse = 0;
	/* ����ָ���Ĳ�����ʼ������TIM2��OC2 */
	TIM_OC2Init(TIM2, &TIM_OCInitStructure); 
	/* ʹ��TIM2��CCR2�ϵ�Ԥװ�ؼĴ��� */
	TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);             

	/* PWM1 Mode configuration: Channel3 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 
	TIM_OCInitStructure.TIM_Pulse = 0;	
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OC3Init(TIM2, &TIM_OCInitStructure);
	TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);

	/* PWM1 Mode configuration: Channel4 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;  
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OC4Init(TIM2, &TIM_OCInitStructure);
	TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);
	TIM_ARRPreloadConfig(TIM2, ENABLE);

	/* TIM2 enable counter */
	TIM_Cmd(TIM2, ENABLE);
}

void vTIM2_PwmOut(int32_t lChannel1, int32_t lChannel2, int32_t lChannel3, int32_t lChannel4)			   //��ʱ��2 pwm�ź����
{
	/* �������ֵ */
	if(lChannel1 >= TIM2_MAX_PWM_PAUSE)
	{
		lChannel1 = TIM2_MAX_PWM_PAUSE;
	}else if(lChannel1 <= TIM2_MIN_PWM_PAUSE)
	{
		lChannel1 = TIM2_MIN_PWM_PAUSE;
	}
	
	if(lChannel2 >= TIM2_MAX_PWM_PAUSE)
	{
		lChannel2 = TIM2_MAX_PWM_PAUSE;
	}else if(lChannel2 <= TIM2_MIN_PWM_PAUSE)
	{
		lChannel2 = TIM2_MIN_PWM_PAUSE;
	}
	
	if(lChannel3 >= TIM2_MAX_PWM_PAUSE)
	{
		lChannel3 = TIM2_MAX_PWM_PAUSE;
	}else if(lChannel3 <= TIM2_MIN_PWM_PAUSE)
	{
		lChannel3 = TIM2_MIN_PWM_PAUSE;
	}
	
	if(lChannel4 >= TIM2_MAX_PWM_PAUSE)
	{
		lChannel4 = TIM2_MAX_PWM_PAUSE;
	}else if(lChannel4 <= TIM2_MIN_PWM_PAUSE)
	{
		lChannel4 = TIM2_MIN_PWM_PAUSE;
	}
	
	TIM2 ->CCR1 = lChannel1;
	TIM2 ->CCR2 = lChannel2;
	TIM2 ->CCR3 = lChannel3;
	TIM2 ->CCR4 = lChannel4;
}

