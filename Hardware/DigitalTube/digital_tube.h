#ifndef _DIGITAL_TUBE_H
#define _DIGITAL_TUBE_H

#include "system.h"

#define DIGITAL_TUBE_DIO  PAout(8)
#define DIGITAL_TUBE_RCLK PAout(4)
#define DIGITAL_TUBE_SCLK PAout(5)

void vDIGITAL_TubeInit(void);
void vDIGITAL_TubeDisplay(uint8_t ulNum,uint8_t ucPos);

#endif
