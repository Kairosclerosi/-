#include "systick.h"						 //延时函数

/*延时1us的计数器值*/
static uint8_t  ucFac_us=0;
/*延时1ms的计数器值*/
static uint16_t usFac_ms=0;

void vSystickDelayInit(void)						 //初始化滴答定时器延时参数
{
	/*选择外部时钟  HCLK/8*/
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
	/*定时1us的计数器值*/
	ucFac_us=SystemCoreClock/8000000;
	/*定时1ms的计数器值*/
	usFac_ms=(u16)ucFac_us*1000;
}

void vSystickDelayUs(uint32_t ulNus)						 //延时1us
{		
	uint32_t ulTemp;
	/*加载定时器计数值*/
	SysTick->LOAD=ulNus*ucFac_us;
	/*清空计数器*/
	SysTick->VAL=0x00;
	/*开始倒数*/
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;
	do
	{
		ulTemp=SysTick->CTRL;
	}
	while(ulTemp&0x01&&!(ulTemp&(1<<16)));//等待时间到达
	/*关闭计数器*/
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;
	/*清空计数器*/
	SysTick->VAL =0X00;
}


void vSystickDelayMs(uint32_t ulNms)				   //延时1ms
{
	uint32_t ulTemp;
	/*加载定时器计数值*/
	SysTick->LOAD=ulNms*usFac_ms;
	/*清空计数器*/
	SysTick->VAL=0x00;
	/*开始倒数*/
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;
	do
	{
		ulTemp=SysTick->CTRL;
	}
	while(ulTemp&0x01&&!(ulTemp&(1<<16)));//等待时间到达
	/*关闭计数器*/
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;
	/*清空计数器*/
	SysTick->VAL =0X00;
}


void vSystickDelayS(uint32_t ulNs)						//延时1s
{
	uint8_t i;
	for(i=0;i<ulNs;i++)
	{
		vSystickDelayMs(1000);
	}
}


/* end of file cppyright reserve by team of Happy Fish */







