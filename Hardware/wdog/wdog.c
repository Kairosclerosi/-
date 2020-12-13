#include "wdog.h"

void vIWDG_Init(uint32_t ucReloadTimeInMs) 	 //独立看门狗初始化
{	
	/* 使能对寄存器IWDG_PR和IWDG_RLR的写操作 */
 	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);  	
	/* 设置IWDG预分频值:设置IWDG预分频值为64 */
	IWDG_SetPrescaler(IWDG_Prescaler_64);  											
	/* 设置IWDG重装载值 */
	IWDG_SetReload(ucReloadTimeInMs);  													
	/* 按照IWDG重装载寄存器的值重装载IWDG计数器 */
	IWDG_ReloadCounter();  													
	/* 使能IWDG */
	IWDG_Enable();  																
}

void vIWDG_Feed(void)	 //喂狗
{   
 	IWDG_ReloadCounter();										   
}

/* end of file cppyright reserve by team of yanjun More information please browse www.yanjuntech.cn */
