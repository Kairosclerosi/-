#include "digital_tube.h"

uint8_t DIGITAL_TUBE_NUM[]={// 0         1          2           3        4         5          6           7        8         9          A           b        C    d          E    F    -
   0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0x8C,0xBF,0xC6,0xA1,0x86,0xFF,0xbf
}; 

void vDIGITAL_TubeInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
	/* 数码管的三个口 */
	DIGITAL_TUBE_DIO = 1;
	DIGITAL_TUBE_RCLK = 1;
	DIGITAL_TUBE_SCLK = 1;
}

void vDIGITAL_TubeOut(uint8_t X)
{
	uint8_t i = 0;
	uint8_t j = 0;
	for(i=8;i>=1;i--)
	{
		DIGITAL_TUBE_SCLK = 0;
		if (X&0x80)
		{
			DIGITAL_TUBE_DIO=1;
		}else
		{ 
			DIGITAL_TUBE_DIO=0;
		}
		DIGITAL_TUBE_SCLK = 1;
		X <<= 1;
		DIGITAL_TUBE_SCLK = 0;
	}
}

void vDIGITAL_TubeDisplay(uint8_t ulNum,uint8_t ucPos)
{
	vDIGITAL_TubeOut(DIGITAL_TUBE_NUM[ulNum]);	
	vDIGITAL_TubeOut(ucPos);	
	DIGITAL_TUBE_RCLK = 0;
	DIGITAL_TUBE_RCLK = 1;	
}

