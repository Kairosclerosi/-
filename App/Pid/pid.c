#include "pid.h"

void vCleanPid(PID_Typedef * pxPid)		 //初始化pxpid值
{
	pxPid->err = 0;					   //清除偏差值
	pxPid->err_last = 0;				//上次偏差
	pxPid->err_last_last = 0;			 //上上次
	pxPid->differential = 0;			 //微分值
	pxPid->integral = 0;				 //积分值
	pxPid->isNeedKi = 0;				//是否需要标志位
	pxPid->OUT = 0;						//清除pid输出值
}

void vCalculatepxPid(PID_Typedef * pxPid)				 //pid计算函数
{
	if(pxPid->isUseDifferentialAhead)			//是否微分先行
		{
		}
	else
	{
		if(((pxPid ->err) > (pxPid -> IntegralSeparation)) || ((pxPid -> err) < (-(pxPid -> IntegralSeparation))))  //若偏差值太大，取消积分项
		{
			pxPid -> isNeedKi = 0;		  //取消积分项
		}
		else
		{
			pxPid -> isNeedKi = 1;		 //保留积分项
			if((pxPid -> integral) > (pxPid -> AntiSaturationIntegral))	//积分正饱和												
			{
				if((pxPid -> err) < 0)											
				{
					pxPid -> integral += (pxPid -> err);			//只需要累加负值				
				}
			}
			else if((pxPid -> integral) < -(pxPid -> AntiSaturationIntegral))  //负饱和
			{
				if((pxPid -> err) > 0)											
				{
					pxPid -> integral += (pxPid -> err);		//累加正值					
				}
			}
			else										  //积分未饱和
			{
				pxPid -> integral += (pxPid -> err);								
			}
		}
		
		if(pxPid -> isNeedKi)		   //pid输出 有无积分项
		{
			pxPid -> OUT = (((pxPid -> Kp) * (pxPid -> err)) + ((pxPid -> Ki) * (pxPid -> integral)) + ((pxPid -> Kd) * (pxPid -> differential)));
		}
		else
		{
			pxPid -> OUT = (((pxPid -> Kp) * (pxPid -> err)) + ((pxPid -> Kd) * (pxPid -> differential)));									
		}	
	}
	
	if(pxPid->isNeedLimitPidOut)		   //pid输出限幅
	{
		if((pxPid->OUT) > (pxPid->pidOutLimitPlus)) 	//判断PID输出和正负限幅值之间的关系
		{
			pxPid->OUT = pxPid->pidOutLimitPlus;		//如果大于正限幅值 就让PID输出值是正限幅值
		}else if((pxPid->OUT) < (pxPid->pidOutLimitMinus))
		{
			pxPid->OUT = (pxPid->pidOutLimitMinus);		//如果小于负限幅值 就让PID输出值是负限幅值
		}
	}
}

