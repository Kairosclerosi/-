#ifndef _MOTOR_H
#define _MOTOR_H

#include "system.h"

#define MOTOR1_1 PEout(15)
#define MOTOR1_2 PEout(14)

#define MOTOR2_1 PEout(12)
#define MOTOR2_2 PEout(13)

void vMOTOR_Init(void);
void vMOTOR_Forward(void);
void vMOTOR_Stop(void);

#endif
