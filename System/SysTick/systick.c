#include "systick.h"						 //��ʱ����

/*��ʱ1us�ļ�����ֵ*/
static uint8_t  ucFac_us=0;
/*��ʱ1ms�ļ�����ֵ*/
static uint16_t usFac_ms=0;

void vSystickDelayInit(void)						 //��ʼ���δ�ʱ����ʱ����
{
	/*ѡ���ⲿʱ��  HCLK/8*/
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
	/*��ʱ1us�ļ�����ֵ*/
	ucFac_us=SystemCoreClock/8000000;
	/*��ʱ1ms�ļ�����ֵ*/
	usFac_ms=(u16)ucFac_us*1000;
}

void vSystickDelayUs(uint32_t ulNus)						 //��ʱ1us
{		
	uint32_t ulTemp;
	/*���ض�ʱ������ֵ*/
	SysTick->LOAD=ulNus*ucFac_us;
	/*��ռ�����*/
	SysTick->VAL=0x00;
	/*��ʼ����*/
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;
	do
	{
		ulTemp=SysTick->CTRL;
	}
	while(ulTemp&0x01&&!(ulTemp&(1<<16)));//�ȴ�ʱ�䵽��
	/*�رռ�����*/
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;
	/*��ռ�����*/
	SysTick->VAL =0X00;
}


void vSystickDelayMs(uint32_t ulNms)				   //��ʱ1ms
{
	uint32_t ulTemp;
	/*���ض�ʱ������ֵ*/
	SysTick->LOAD=ulNms*usFac_ms;
	/*��ռ�����*/
	SysTick->VAL=0x00;
	/*��ʼ����*/
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;
	do
	{
		ulTemp=SysTick->CTRL;
	}
	while(ulTemp&0x01&&!(ulTemp&(1<<16)));//�ȴ�ʱ�䵽��
	/*�رռ�����*/
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;
	/*��ռ�����*/
	SysTick->VAL =0X00;
}


void vSystickDelayS(uint32_t ulNs)						//��ʱ1s
{
	uint8_t i;
	for(i=0;i<ulNs;i++)
	{
		vSystickDelayMs(1000);
	}
}


/* end of file cppyright reserve by team of Happy Fish */







