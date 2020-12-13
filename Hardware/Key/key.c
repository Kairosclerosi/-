#include "key.h"

/* key1 */
uint8_t ucKey2State = 0;

/* �������� ִ�еĶ��� */
#define KEY2_ACTION		(uint8_t)2

void vKEY_Init(void)								 //��ʼ������IO��
{
 	GPIO_InitTypeDef GPIO_InitStructure;

	/* ��ʼ��PA12 PC10 PB14 PB13 PB12  �������� */
 	RCC_APB2PeriphClockCmd(KEY2_RCC
												|RCC_APB2Periph_AFIO,ENABLE);
	
	/* PC13 */
	GPIO_InitStructure.GPIO_Pin = KEY2_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
 	GPIO_Init(KEY2_PORT, &GPIO_InitStructure);

}

void vKEY_Scan(void)							//ɨ�谴��
{
	/*����ɨ�軺����*/
	static uint8_t ucKey2Buffer = 0xff;
	
	/*��ȡ����ֵ���뻺����*/
	ucKey2Buffer = (ucKey2Buffer << 1)| KEY2;
	
	/* ��������˴�Ϊ0��Ϊ0 */
	if(ucKey2Buffer == 0x00)
	{
		ucKey2State = 0;
	}else if(ucKey2Buffer == 0xff)
	{
		ucKey2State = 1;
	}
	
}

/* �����õ��������� */
uint8_t ucKeyIdFlag = 0;
uint32_t ui_KeyCount = 0;
void vKEY_Action(uint8_t ucActionFlag)
{
	switch(ucActionFlag)
	{
		case KEY2_ACTION:
			ucKeyIdFlag = 2;
			ui_KeyCount++;
			break;
		default:
			break;
	}
}


void vKEY_Driver(void)					  //��������
{
	static uint8_t ucKey2Backup = 1;
	
	if(ucKey2Backup != ucKey2State)
	{
		if(ucKey2Backup == 0)
		{
			vKEY_Action(KEY2_ACTION);			
		}
		ucKey2Backup = ucKey2State;
	}
	
}

