#include "pid.h"

void vCleanPid(PID_Typedef * pxPid)		 //��ʼ��pxpidֵ
{
	pxPid->err = 0;					   //���ƫ��ֵ
	pxPid->err_last = 0;				//�ϴ�ƫ��
	pxPid->err_last_last = 0;			 //���ϴ�
	pxPid->differential = 0;			 //΢��ֵ
	pxPid->integral = 0;				 //����ֵ
	pxPid->isNeedKi = 0;				//�Ƿ���Ҫ��־λ
	pxPid->OUT = 0;						//���pid���ֵ
}

void vCalculatepxPid(PID_Typedef * pxPid)				 //pid���㺯��
{
	if(pxPid->isUseDifferentialAhead)			//�Ƿ�΢������
		{
		}
	else
	{
		if(((pxPid ->err) > (pxPid -> IntegralSeparation)) || ((pxPid -> err) < (-(pxPid -> IntegralSeparation))))  //��ƫ��ֵ̫��ȡ��������
		{
			pxPid -> isNeedKi = 0;		  //ȡ��������
		}
		else
		{
			pxPid -> isNeedKi = 1;		 //����������
			if((pxPid -> integral) > (pxPid -> AntiSaturationIntegral))	//����������												
			{
				if((pxPid -> err) < 0)											
				{
					pxPid -> integral += (pxPid -> err);			//ֻ��Ҫ�ۼӸ�ֵ				
				}
			}
			else if((pxPid -> integral) < -(pxPid -> AntiSaturationIntegral))  //������
			{
				if((pxPid -> err) > 0)											
				{
					pxPid -> integral += (pxPid -> err);		//�ۼ���ֵ					
				}
			}
			else										  //����δ����
			{
				pxPid -> integral += (pxPid -> err);								
			}
		}
		
		if(pxPid -> isNeedKi)		   //pid��� ���޻�����
		{
			pxPid -> OUT = (((pxPid -> Kp) * (pxPid -> err)) + ((pxPid -> Ki) * (pxPid -> integral)) + ((pxPid -> Kd) * (pxPid -> differential)));
		}
		else
		{
			pxPid -> OUT = (((pxPid -> Kp) * (pxPid -> err)) + ((pxPid -> Kd) * (pxPid -> differential)));									
		}	
	}
	
	if(pxPid->isNeedLimitPidOut)		   //pid����޷�
	{
		if((pxPid->OUT) > (pxPid->pidOutLimitPlus)) 	//�ж�PID����������޷�ֵ֮��Ĺ�ϵ
		{
			pxPid->OUT = pxPid->pidOutLimitPlus;		//����������޷�ֵ ����PID���ֵ�����޷�ֵ
		}else if((pxPid->OUT) < (pxPid->pidOutLimitMinus))
		{
			pxPid->OUT = (pxPid->pidOutLimitMinus);		//���С�ڸ��޷�ֵ ����PID���ֵ�Ǹ��޷�ֵ
		}
	}
}

