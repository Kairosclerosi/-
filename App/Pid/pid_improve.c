#include "pid_improve.h"

void vPidCalculated(PID_ModifiableTypedef * pxModifiablePid,
										PID_NonModifiableTypedef * pxCanNotMotifyPid)
{
	float fPidOutBuffer = 0.0f;
	/* �����ж��Ƿ�Ҫʹ��΢������ ΢������ʹ�������뾭���Եı䶯��pxPid���� */
	if(pxModifiablePid->ulIsUseDifferentialAhead)
	{
		/* ʹ��΢�����в��� ���ַ��� �����ͻ��� */
		/* ��ʱ��û��ʵ�� ΢������ ��Ϊ ��� һֱû���õ� */
	}else
	{
		/* ��ʹ��΢�����в��� ���ַ��� �����ͻ��� */
		/* �����ʱ��ƫ��ֵ̫���ˣ���ôȡ�������� */
		
		if(((pxCanNotMotifyPid ->fErr) > (pxModifiablePid -> fIntegralSeparation)) || ((pxCanNotMotifyPid -> fErr) < (-(pxModifiablePid -> fIntegralSeparation))))
		{
			/* ȡ�������� */
			pxCanNotMotifyPid -> ulIsNeedKi = 0;
		}else
		{
			/* ���������� */
			pxCanNotMotifyPid -> ulIsNeedKi = 1;
			/*-------------------���ַ���Ϳ����ͻ���----------------------------*/
			/* pxPid���ִﵽ���ֵ�����pxPid��������ڿ����ͻ��ֵ������ */
			if((pxCanNotMotifyPid -> fIntegral) > (pxModifiablePid -> fAntiSaturationIntegral))													
			{
				/* �����ͻ��� */
				if((pxCanNotMotifyPid ->fErr) < 0)											
				{
					/* ֻ�ۼӸ�ֵ */
					pxCanNotMotifyPid -> fIntegral += (pxCanNotMotifyPid ->fErr);							
				}
			/* pxPid���ִﵽ�������ֵ�����pxPid��������ڸ��Ŀ����ͻ��ֵ������ */
			}else if((pxCanNotMotifyPid -> fIntegral) < -(pxModifiablePid -> fAntiSaturationIntegral))
			{
				/* �����ͻ��� */
				if((pxCanNotMotifyPid ->fErr) > 0)											
				{
					/* ֻ�ۼ���ֵ */
					pxCanNotMotifyPid -> fIntegral += (pxCanNotMotifyPid ->fErr);							
				}
			/* pxPid�������������pxPid��������� */
			}else
			{
				/* ����ֵ�ô�С�������ۼ������� */
				pxCanNotMotifyPid -> fIntegral  += (pxCanNotMotifyPid -> fErr);								
			}
		}
		
		/* ����pxPid��� */
		if(pxCanNotMotifyPid -> ulIsNeedKi)
		{
			/* pxPid��� = ����*ƫ�� + ����*ƫ����� + ΢��*ƫ��΢�� */
			fPidOutBuffer = (((pxModifiablePid -> fKp) * (pxCanNotMotifyPid -> fErr)) 
																		+ ((pxModifiablePid -> fKi) * (pxCanNotMotifyPid -> fIntegral))
																		+ ((pxModifiablePid -> fKd) * (pxCanNotMotifyPid -> fDifferential)));
		}else
		{
			/* pxPid��� = ����*ƫ�� + ΢��*ƫ��΢�� */
			fPidOutBuffer = (((pxModifiablePid -> fKp) * (pxCanNotMotifyPid -> fErr)) 
																		+ ((pxModifiablePid -> fKd) * (pxCanNotMotifyPid -> fDifferential)));
								
		}	
	}
	
	/* pxPid����޷� */
	if(pxModifiablePid->ulIsNeedLimitPidOut)
	{
		/* �ж�PID����������޷�ֵ֮��Ĺ�ϵ */
		if((fPidOutBuffer) > (pxModifiablePid->fPidOutLimitPlus)) 
		{
			/* ����������޷�ֵ ����PID���ֵ�����޷�ֵ */
			fPidOutBuffer = pxModifiablePid->fPidOutLimitPlus;
		}else if((fPidOutBuffer) < (pxModifiablePid->fPidOutLimitMinus))
		{
			/* ���С�ڸ��޷�ֵ ����PID���ֵ�Ǹ��޷�ֵ */
			fPidOutBuffer = (pxModifiablePid->fPidOutLimitMinus);
		}
	}
	/* ������ʱ���и�Ƶ��������� pid�����ͨ�˲�ѡ�� */
	if(pxModifiablePid ->ulIsNeedPidOutLpf)
	{
		pxCanNotMotifyPid -> fOut = (1 - pxModifiablePid ->fLpfCoefficient) * pxCanNotMotifyPid -> fOut 
																+ pxModifiablePid ->fLpfCoefficient * fPidOutBuffer;		
	}else
	{
		pxCanNotMotifyPid -> fOut = fPidOutBuffer;
	}
}


/* end of file cppyright reserve by team of yanjun More information please browse www.yanjun.tech */
