#include "wdog.h"

void vIWDG_Init(uint32_t ucReloadTimeInMs) 	 //�������Ź���ʼ��
{	
	/* ʹ�ܶԼĴ���IWDG_PR��IWDG_RLR��д���� */
 	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);  	
	/* ����IWDGԤ��Ƶֵ:����IWDGԤ��ƵֵΪ64 */
	IWDG_SetPrescaler(IWDG_Prescaler_64);  											
	/* ����IWDG��װ��ֵ */
	IWDG_SetReload(ucReloadTimeInMs);  													
	/* ����IWDG��װ�ؼĴ�����ֵ��װ��IWDG������ */
	IWDG_ReloadCounter();  													
	/* ʹ��IWDG */
	IWDG_Enable();  																
}

void vIWDG_Feed(void)	 //ι��
{   
 	IWDG_ReloadCounter();										   
}

/* end of file cppyright reserve by team of yanjun More information please browse www.yanjuntech.cn */
