#include "main.h"

void vAllInit(void);
void vMainErrorHandler(SystemInitFaultTypedef xFaultType);

extern uint32_t ulTmr10MsFlag;

int main(void)
{	
	//static float fLeft = 0.0f;
	//static float fRight = 0.0f;
	vAllInit();
	while(1)				 //feeddog
	{
		vIWDG_Feed();
		vKEY_Driver();
	/*	if(ulTmr10MsFlag == 1)
		{
			ulTmr10MsFlag = 0;
			fLeft = (float)((float)ulADC1Channel8Value / 1241.0f);
			fRight = (float)((float)ulADC1Channel9Value / 1241.0f);
			vOLED_ShowNum(64,0,ulADC1Channel8Value,4,16);
			vOLED_ShowNum(64,2,ulADC1Channel9Value,4,16);
			vOLED_ShowNum(64,4,(uint32_t)(fLeft * 1000),4,16);
			vOLED_ShowNum(64,6,(uint32_t)(fRight * 1000),4,16);
		}	
	*/
// 		vDIGITAL_TubeDisplay(2,0x02);
// 		vSystickDelayMs(1);
// 		vDIGITAL_TubeDisplay(3,0x01);
// 		vSystickDelayMs(1);
	}
}


void vAllInit(void)					//系统初始化
{
	/* 串口调试输出信息 */
	uint8_t ucDebugMsg[] = "System Init Success!";
	/* 配置NVIC向量分组 */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	/* 初始化 SYSTICK 定时器 */
	vSystickDelayInit(); 	
	/* 串口1初始化 使用DMA传输数据 */
	vUSART1_Init(115200);
	/* IIC初始化 */
//	vOLEDI2C_Init();
	/* OLED */
//	vOLED_Init();
	/* 按键初始化 */
	vKEY_Init();
	/* MOTOR初始化 */
	vMOTOR_Init();
	/* 干簧管初始化 用于检测磁铁 */
	//vREED_SwitchInit();
	/* ADC1初始化操作 */
	vADC1_Init();
	/* 数码管初始化 */
//	vDIGITAL_TubeInit();
	/* pwm初始化 */
	vTIM2_PwmInit(4,1000);
	/* 看门狗初始化 */
	vIWDG_Init(IWDG_PERIOD_2000MS);
/*	vOLED_CLS();
	vOLED_CLS();
	vOLED_CLS();
	vOLED_ShowString(0,0,"LEFT:");
	vOLED_ShowString(0,2,"RIGHT:");	
	vOLED_ShowString(0,4,"LEFT:");
	vOLED_ShowString(0,6,"RIGHT:");			
	vOLED_ShowString(96,4,"mv");
	vOLED_ShowString(96,6,"mv");	*/
	/* 定时器初始化 */
	vTIM3_Init(TIMER3_CALLBACK_FREQUENCY_1000HZ);
	/* 提示初始化成功 */
 	vDebugSendString(ucDebugMsg, sizeof(ucDebugMsg)- 1, 1); 

	/* 用蜂鸣器 提醒 初始化成功 */
}


void vMainErrorHandler(SystemInitFaultTypedef xFaultType)				//系统初始化错误回调函数
{
	/* 定义的一些字符串 */
	uint8_t ucPromoteString0[] = "system will reset \r\n";
	uint8_t ucPromoteString1[] = "no example device detected \r\n";
	
	/* 提示错误类型 */
	switch(xFaultType)
	{
		case NO_EXAMPLE_DEVICE:
			vDebugSendString(ucPromoteString1, sizeof(ucPromoteString1)-1, 1);
			break;
		default:
			break;
	}
	
	/* 先延时一段时间 */
	vSystickDelayMs(100);
	/* 提示系统即将重启 */
	vDebugSendString(ucPromoteString0, sizeof(ucPromoteString0)-1, 1);
	
	/* 关闭所有中断 */
	__set_FAULTMASK(1);
	/* 复位 */
	NVIC_SystemReset();
	/* 捕获错误 */
	while(1)
	{
		
	}	
}

