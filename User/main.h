#ifndef _MAIN_H
#define _MAIN_H

#include "system.h"
#include "usart1_dma.h"
#include "util.h"
#include "wdog.h"
#include "adc1.h"
#include "oled_iic.h"
#include "oled.h"
#include "timer3.h"
#include "digital_tube.h"
#include "motor.h"
#include "key.h"
#include "reed_switch.h"
#include "timer2_pwm.h"

/* 设备初始化失败，对应的设备ID */
typedef enum 
{
	NO_EXAMPLE_DEVICE = 0,
}SystemInitFaultTypedef;

#endif

/* end of file cppyright reserve by team of yanjun ,More information please browse www.yanjuntech.cn */
