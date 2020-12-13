#include "motor.h"				   //电机速度

void vMOTOR_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	/* GPIOB clock enable */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);

	/* GPIOA Configuration:TIM2 Channel1, 2, 2 and 4 as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_11 | GPIO_Pin_13 |GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;                                       
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &GPIO_InitStructure);	
	
	MOTOR1_1 = 0;
	MOTOR1_2 = 0;
	MOTOR2_1 = 0;
	MOTOR2_2 = 0;
}

void vMOTOR_Forward(void)
{
	MOTOR1_1 = 1;
	MOTOR1_2 = 0;
	MOTOR2_1 = 0;
	MOTOR2_2 = 1;	
}

void vMOTOR_Stop(void)
{
	MOTOR1_1 = 0;
	MOTOR1_2 = 0;
	MOTOR2_1 = 0;
	MOTOR2_2 = 0;	
}
