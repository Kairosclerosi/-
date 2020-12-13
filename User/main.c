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


void vAllInit(void)					//ϵͳ��ʼ��
{
	/* ���ڵ��������Ϣ */
	uint8_t ucDebugMsg[] = "System Init Success!";
	/* ����NVIC�������� */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	/* ��ʼ�� SYSTICK ��ʱ�� */
	vSystickDelayInit(); 	
	/* ����1��ʼ�� ʹ��DMA�������� */
	vUSART1_Init(115200);
	/* IIC��ʼ�� */
//	vOLEDI2C_Init();
	/* OLED */
//	vOLED_Init();
	/* ������ʼ�� */
	vKEY_Init();
	/* MOTOR��ʼ�� */
	vMOTOR_Init();
	/* �ɻɹܳ�ʼ�� ���ڼ����� */
	//vREED_SwitchInit();
	/* ADC1��ʼ������ */
	vADC1_Init();
	/* ����ܳ�ʼ�� */
//	vDIGITAL_TubeInit();
	/* pwm��ʼ�� */
	vTIM2_PwmInit(4,1000);
	/* ���Ź���ʼ�� */
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
	/* ��ʱ����ʼ�� */
	vTIM3_Init(TIMER3_CALLBACK_FREQUENCY_1000HZ);
	/* ��ʾ��ʼ���ɹ� */
 	vDebugSendString(ucDebugMsg, sizeof(ucDebugMsg)- 1, 1); 

	/* �÷����� ���� ��ʼ���ɹ� */
}


void vMainErrorHandler(SystemInitFaultTypedef xFaultType)				//ϵͳ��ʼ������ص�����
{
	/* �����һЩ�ַ��� */
	uint8_t ucPromoteString0[] = "system will reset \r\n";
	uint8_t ucPromoteString1[] = "no example device detected \r\n";
	
	/* ��ʾ�������� */
	switch(xFaultType)
	{
		case NO_EXAMPLE_DEVICE:
			vDebugSendString(ucPromoteString1, sizeof(ucPromoteString1)-1, 1);
			break;
		default:
			break;
	}
	
	/* ����ʱһ��ʱ�� */
	vSystickDelayMs(100);
	/* ��ʾϵͳ�������� */
	vDebugSendString(ucPromoteString0, sizeof(ucPromoteString0)-1, 1);
	
	/* �ر������ж� */
	__set_FAULTMASK(1);
	/* ��λ */
	NVIC_SystemReset();
	/* ������� */
	while(1)
	{
		
	}	
}

