#include "pid_improve.h"

void vPidCalculated(PID_ModifiableTypedef * pxModifiablePid,
										PID_NonModifiableTypedef * pxCanNotMotifyPid)
{
	float fPidOutBuffer = 0.0f;
	/* 先来判断是否要使用微分先行 微分先行使用与输入经常性的变动的pxPid控制 */
	if(pxModifiablePid->ulIsUseDifferentialAhead)
	{
		/* 使用微分先行策略 积分分离 抗饱和积分 */
		/* 暂时还没有实现 微分先行 因为 这块 一直没有用到 */
	}else
	{
		/* 不使用微分先行策略 积分分离 抗饱和积分 */
		/* 如果此时的偏差值太大了，那么取消积分项 */
		
		if(((pxCanNotMotifyPid ->fErr) > (pxModifiablePid -> fIntegralSeparation)) || ((pxCanNotMotifyPid -> fErr) < (-(pxModifiablePid -> fIntegralSeparation))))
		{
			/* 取消积分项 */
			pxCanNotMotifyPid -> ulIsNeedKi = 0;
		}else
		{
			/* 保留积分项 */
			pxCanNotMotifyPid -> ulIsNeedKi = 1;
			/*-------------------积分分离和抗饱和积分----------------------------*/
			/* pxPid积分达到最大值，如果pxPid的输出大于抗饱和积分的输出了 */
			if((pxCanNotMotifyPid -> fIntegral) > (pxModifiablePid -> fAntiSaturationIntegral))													
			{
				/* 抗饱和积分 */
				if((pxCanNotMotifyPid ->fErr) < 0)											
				{
					/* 只累加负值 */
					pxCanNotMotifyPid -> fIntegral += (pxCanNotMotifyPid ->fErr);							
				}
			/* pxPid积分达到负的最大值，如果pxPid的输出大于负的抗饱和积分的输出了 */
			}else if((pxCanNotMotifyPid -> fIntegral) < -(pxModifiablePid -> fAntiSaturationIntegral))
			{
				/* 抗饱和积分 */
				if((pxCanNotMotifyPid ->fErr) > 0)											
				{
					/* 只累加正值 */
					pxCanNotMotifyPid -> fIntegral += (pxCanNotMotifyPid ->fErr);							
				}
			/* pxPid积分正常，如果pxPid的输出正常 */
			}else
			{
				/* 积分值得大小正常，累加误差积分 */
				pxCanNotMotifyPid -> fIntegral  += (pxCanNotMotifyPid -> fErr);								
			}
		}
		
		/* 计算pxPid输出 */
		if(pxCanNotMotifyPid -> ulIsNeedKi)
		{
			/* pxPid输出 = 比例*偏差 + 积分*偏差积分 + 微分*偏差微分 */
			fPidOutBuffer = (((pxModifiablePid -> fKp) * (pxCanNotMotifyPid -> fErr)) 
																		+ ((pxModifiablePid -> fKi) * (pxCanNotMotifyPid -> fIntegral))
																		+ ((pxModifiablePid -> fKd) * (pxCanNotMotifyPid -> fDifferential)));
		}else
		{
			/* pxPid输出 = 比例*偏差 + 微分*偏差微分 */
			fPidOutBuffer = (((pxModifiablePid -> fKp) * (pxCanNotMotifyPid -> fErr)) 
																		+ ((pxModifiablePid -> fKd) * (pxCanNotMotifyPid -> fDifferential)));
								
		}	
	}
	
	/* pxPid输出限幅 */
	if(pxModifiablePid->ulIsNeedLimitPidOut)
	{
		/* 判断PID输出和正负限幅值之间的关系 */
		if((fPidOutBuffer) > (pxModifiablePid->fPidOutLimitPlus)) 
		{
			/* 如果大于正限幅值 就让PID输出值是正限幅值 */
			fPidOutBuffer = pxModifiablePid->fPidOutLimitPlus;
		}else if((fPidOutBuffer) < (pxModifiablePid->fPidOutLimitMinus))
		{
			/* 如果小于负限幅值 就让PID输出值是负限幅值 */
			fPidOutBuffer = (pxModifiablePid->fPidOutLimitMinus);
		}
	}
	/* 由于有时候有高频干扰这里加 pid输出低通滤波选项 */
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
