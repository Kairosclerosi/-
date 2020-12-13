#ifndef _PID_IMPROVE_H
#define _PID_IMPROVE_H

#include "system.h"

typedef struct
{ 
	const float fKp; 														//����ϵ��
	const float fKi; 														//����ϵ��
	const float fKd; 														//΢��ϵ��
	const float fIntegralSeparation;						//���ַ�����ֵ
	const float fAntiSaturationIntegral;				//�����ͻ�����ֵ
	const uint32_t ulIsUseDifferentialAhead;		//�Ƿ�ʹ��΢�����е�PID����
	const uint32_t ulIsNeedLimitPidOut;					//�Ƿ���Ҫ����PID�������
	const float fPidOutLimitPlus;								//PID���޷�ֵ
	const float fPidOutLimitMinus;							//PID���޷�ֵ
	const uint32_t ulIsNeedPidDeadZone;					//�Ƿ���Ҫpid����
	const float fPidDeadZoneVal;								//pid����������ֵ
	const uint32_t ulIsNeedPidOutLpf;						//�Ƿ���Ҫpid�������ͨ�˲� LOW PASS FILTER
	const float fLpfCoefficient;			//PID��ͨ�˲�����ϵ��
}PID_ModifiableTypedef;												//������Ϊ�޸ĵ�pid����

typedef struct
{ 
	float fIntegral; 													//����ֵ
	float fErr; 															//����ƫ��
	float fErrLast;														//�ϴ�ƫ��
	float fErrLastLast;												//���ϴ�ƫ��
	uint32_t ulIsNeedKi;											//�Ƿ���Ҫ���֣����ڻ��ַ���
	float fDifferential;											//����΢��ֵ
	float	fOut;																//PID���
}PID_NonModifiableTypedef;									//��������Ϊ�޸ģ����ǳ�������޸ĵ�pid����

#endif

/* end of file cppyright reserve by team of yanjun More information please browse www.yanjun.tech */
