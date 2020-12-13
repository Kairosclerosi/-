#include "control.h"

uint32_t ulTmr10MsFlag = 0;
uint32_t ulIsHaveMagnetFlag = 0;
uint32_t ulIsCarGoFlag = 0;

int32_t lBaseDuty = 200;	//设定基准速度
	  
#define THRESHOLD (int32_t)300

void vCarCalculatePid(void)
{
	static int32_t lLeftSubtractRight = 0;
	static int32_t lLeftDutyVal = 0;
	static int32_t lRightDutyVal = 0;	
	static int32_t lPidOut = 0;
	static PID_Typedef xPID_CarStraightPid = 		//设定直线pid参数
	{
		-0.6,		//比例系数
		0,		//积分系数
		-200,		//微分系数
		
		/* 以下参数程序自动设定 */
		0,		//积分值
		0,		//本次偏差
		0,		//上次偏差
		0,		//上上次偏差
		0,		//是否需要积分，用于积分分离
		0,		//本次微分值
		
		/* 需要手动设置的PID参数 */		
		0,		//积分分离阈值
		0,	//抗饱和积分阈值
		0,		//是否使用微分先行的PID策略
		1,		//是否需要限制PID输出幅度
		800,	//PID限幅值
		-800,	//PID负限幅值
		
		0			//PID输出
	};	

	static PID_Typedef xPID_CarCurvePid = 		 //设定弯道pid参数
	{
		-1.8,		//比例系数
		0,		//积分系数
		-300,		//微分系数
		
		/* 程序中自动完成计算的参数，不能手动改 */
		0,		//积分值
		0,		//本次偏差
		0,		//上次偏差
		0,		//上上次偏差
		0,		//是否需要积分，用于积分分离
		0,		//本次微分值
		
		/* 需要手动设置的PID参数 */		
		0,		//积分分离阈值
		0,	//抗饱和积分阈值
		0,		//是否使用微分先行的PID策略
		1,		//是否需要限制PID输出幅度
		600,	//PID限幅值
		-600,	//PID负限幅值
		
		0			//PID输出
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


void TIM3_IRQHandler(void)   		//定时器3中断服务函数								
{
	static uint32_t ulTmr2Ms = 0;
	static uint32_t ulTmr50Ms = 0;
	static uint32_t ulTmr10Ms = 0;
	static uint32_t ulTmr1000Ms = 0;
	static uint32_t ulTmrDelay3000Ms = 0;

	/* 判断是否更新中断 UIF 位是否置位 */
	if (TIM3->SR & (uint32_t)(1)) 											
	{
		if(++ulTmr2Ms >= 2)
		{
			ulTmr2Ms = 0;
			vKEY_Scan();	 //按键扫描
			vCarCalculatePid();		//循迹pid
		}
		
		if((ui_KeyCount % 2) == 0)
		{
			ucKeyIdFlag = 0;
			/* 基准油门 */
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
		/* 标志位清零 */
		TIM3 -> SR &= (uint32_t)(~1);										
	}
}
