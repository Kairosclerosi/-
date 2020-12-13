#ifndef _PID_IMPROVE_H
#define _PID_IMPROVE_H

#include "system.h"

typedef struct
{ 
	const float fKp; 														//比例系数
	const float fKi; 														//积分系数
	const float fKd; 														//微分系数
	const float fIntegralSeparation;						//积分分离阈值
	const float fAntiSaturationIntegral;				//抗饱和积分阈值
	const uint32_t ulIsUseDifferentialAhead;		//是否使用微分先行的PID策略
	const uint32_t ulIsNeedLimitPidOut;					//是否需要限制PID输出幅度
	const float fPidOutLimitPlus;								//PID正限幅值
	const float fPidOutLimitMinus;							//PID负限幅值
	const uint32_t ulIsNeedPidDeadZone;					//是否需要pid死区
	const float fPidDeadZoneVal;								//pid死区的设置值
	const uint32_t ulIsNeedPidOutLpf;						//是否需要pid的输出低通滤波 LOW PASS FILTER
	const float fLpfCoefficient;			//PID低通滤波器的系数
}PID_ModifiableTypedef;												//可以人为修改的pid参数

typedef struct
{ 
	float fIntegral; 													//积分值
	float fErr; 															//本次偏差
	float fErrLast;														//上次偏差
	float fErrLastLast;												//上上次偏差
	uint32_t ulIsNeedKi;											//是否需要积分，用于积分分离
	float fDifferential;											//本次微分值
	float	fOut;																//PID输出
}PID_NonModifiableTypedef;									//不可以人为修改，但是程序可以修改的pid数据

#endif

/* end of file cppyright reserve by team of yanjun More information please browse www.yanjun.tech */
