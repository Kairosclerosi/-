#ifndef _PID_H
#define _PID_H

#include "system.h"

typedef struct
{ 
	const float Kp; 													//����ϵ��
	const float Ki; 													//����ϵ��
	const float Kd; 													//΢��ϵ��
	float integral; 													//����ֵ
	float err; 																//����ƫ��
	float err_last;														//�ϴ�ƫ��
	float err_last_last;											//���ϴ�ƫ��
	uint32_t isNeedKi;												//�Ƿ���Ҫ���֣����ڻ��ַ���
	float differential;												//����΢��ֵ
	const float IntegralSeparation;						//���ַ�����ֵ
	const float AntiSaturationIntegral;				//�����ͻ�����ֵ
	const uint32_t isUseDifferentialAhead;		//�Ƿ�ʹ��΢�����е�PID����
	const uint32_t isNeedLimitPidOut;					//�Ƿ���Ҫ����PID�������
	const float pidOutLimitPlus;							//PID���޷�ֵ
	const float pidOutLimitMinus;							//PID���޷�ֵ
	float	OUT;																//PID���
}PID_Typedef;

void vCleanPid(PID_Typedef * pxPid);
void vCalculatepxPid(PID_Typedef * pxPid);

#endif
