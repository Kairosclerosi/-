#include "reed_switch.h"	  //电感传感器 

void vREED_SwitchInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	/* GPIOC clock enable */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE);

	/* GPIOA Configuration:TIM2 Channel1, 2, 2 and 4 as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;                                       
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOG, &GPIO_InitStructure);	
}




