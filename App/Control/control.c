#include "control.h"

uint32_t ulTmr10MsFlag = 0;
uint32_t ulIsHaveMagnetFlag = 0;
uint32_t ulIsCarGoFlag = 0;

int32_t lBaseDuty = 200;	//�趨��׼�ٶ�
	  
#define THRESHOLD (int32_t)300

void vCarCalculatePid(void)
{
	static int32_t lLeftSubtractRight = 0;
	static int32_t lLeftDutyVal = 0;
	static int32_t lRightDutyVal = 0;	
	static int32_t lPidOut = 0;
	static PID_Typedef xPID_CarStraightPid = 		//�趨ֱ��pid����
	{
		-0.6,		//����ϵ��
		0,		//����ϵ��
		-200,		//΢��ϵ��
		
		/* ���²��������Զ��趨 */
		0,		//����ֵ
		0,		//����ƫ��
		0,		//�ϴ�ƫ��
		0,		//���ϴ�ƫ��
		0,		//�Ƿ���Ҫ���֣����ڻ��ַ���
		0,		//����΢��ֵ
		
		/* ��Ҫ�ֶ����õ�PID���� */		
		0,		//���ַ�����ֵ
		0,	//�����ͻ�����ֵ
		0,		//�Ƿ�ʹ��΢�����е�PID����
		1,		//�Ƿ���Ҫ����PID�������
		800,	//PID�޷�ֵ
		-800,	//PID���޷�ֵ
		
		0			//PID���
	};	

	static PID_Typedef xPID_CarCurvePid = 		 //�趨���pid����
	{
		-1.8,		//����ϵ��
		0,		//����ϵ��
		-300,		//΢��ϵ��
		
		/* �������Զ���ɼ���Ĳ����������ֶ��� */
		0,		//����ֵ
		0,		//����ƫ��
		0,		//�ϴ�ƫ��
		0,		//���ϴ�ƫ��
		0,		//�Ƿ���Ҫ���֣����ڻ��ַ���
		0,		//����΢��ֵ
		
		/* ��Ҫ�ֶ����õ�PID���� */		
		0,		//���ַ�����ֵ
		0,	//�����ͻ�����ֵ
		0,		//�Ƿ�ʹ��΢�����е�PID����
		1,		//�Ƿ���Ҫ����PID�������
		600,	//PID�޷�ֵ
		-600,	//PID���޷�ֵ
		
		0			//PID���
	};	
	
	lLeftSubtractRight = (int32_t)ulADC1Channel8Value - (int32_t)ulADC1Channel9Value;
	
	if((lLeftSubtractRight <= THRESHOLD) && (lLeftSubtractRight >= -THRESHOLD))
	{
		xPID_CarStraightPid.err = (float)((int32_t)0 - lLeftSubtractRight);
		xPID_CarStraightPid.differential = xPID_CarStraightPid.err - xPID_CarStraightPid.err_last;
		xPID_CarStraightPid.err_last = xPID_CarStraightPid.err;
		vCalculatepxPid(&xPID_CarStraightPid);	
		lBaseDuty = 250;
		lPidOut = (int32_t)xPID_CarStraightPid.OUT;
	}else 
	{
		xPID_CarCurvePid.err = (float)((int32_t)0 - lLeftSubtractRight);
		xPID_CarCurvePid.differential = xPID_CarCurvePid.err - xPID_CarCurvePid.err_last;
		xPID_CarCurvePid.err_last = xPID_CarCurvePid.err;
		vCalculatepxPid(&xPID_CarCurvePid);			
		lBaseDuty = 80;
		lPidOut = (int32_t)xPID_CarCurvePid.OUT;
	}

	lLeftDutyVal = lBaseDuty - lPidOut;
	lRightDutyVal = lBaseDuty + lPidOut;	
	if((ui_KeyCount % 2) == 0)
	{
		vTIM2_PwmOut(lLeftDutyVal,lRightDutyVal,0,0);
	}else
	{
		vTIM2_PwmOut(0,0,0,0);
	}
	
}


void TIM3_IRQHandler(void)   		//��ʱ��3�жϷ�����								
{
	static uint32_t ulTmr2Ms = 0;
	static uint32_t ulTmr50Ms = 0;
	static uint32_t ulTmr10Ms = 0;
	static uint32_t ulTmr1000Ms = 0;
	static uint32_t ulTmrDelay3000Ms = 0;

	/* �ж��Ƿ�����ж� UIF λ�Ƿ���λ */
	if (TIM3->SR & (uint32_t)(1)) 											
	{
		if(++ulTmr2Ms >= 2)
		{
			ulTmr2Ms = 0;
			vKEY_Scan();	 //����ɨ��
			vCarCalculatePid();		//ѭ��pid
		}
		
		if((ui_KeyCount % 2) == 0)
		{
			ucKeyIdFlag = 0;
			/* ��׼���� */
			vMOTOR_Forward();
		}else
		{
			vMOTOR_Stop();
		}

		if(++ulTmr10Ms >= 10)
		{
			ulTmr10Ms = 0;
			ulTmr10MsFlag = 1;
		}
		if(++ulTmr1000Ms >= 1000)
		{
			ulTmr1000Ms = 0;
		}
		/* ��־λ���� */
		TIM3 -> SR &= (uint32_t)(~1);										
	}
}
