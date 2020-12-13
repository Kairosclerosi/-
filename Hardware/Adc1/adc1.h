#ifndef _ADC1_H
#define	_ADC1_H

#include "system.h"

/* ADC1的通道数量 */
#define ADC1_CHANNEL_NUMBER	((uint32_t)2)

/* ADC1采样数组长度 ，总共有4个通道，采样频率为 50KHZ */
//#define NOFCHANEL 							((uint32_t)200)
#define ADC1_SAMPLE_NUM_ONE_CHANNEL 	((uint32_t)NOFCHANEL/ADC1_CHANNEL_NUMBER)

/* ADC1数据寄存器地址 */
#define ADC1_DR_Address    ((uint32_t)0x40012400+0x4c)

/*
	下面说明，每个通道，对应的含义
	ADC1的通道4	---	右手的上下	---	范围为 0 --- 4092	--- 向上增大，向下减小 --- 中间值 --- 2010 +- 50
	ADC1的通道8	---	左手的微调	---	范围为 0 --- 4095	--- 顺时针减小，逆时针增大 --- 中间值 --- 2000左右
	ADC1的通道9	---	右手的微调	---	范围为 0 --- 4094	--- 顺时针减小，逆时针增大 --- 中间值 --- 2000左右
	ADC1的通道12	---	左手的上下	---	范围为140 ---4095	--- 向上增大，向下减小 --- 中间值 --- 2000左右
	ADC1的通道13	---	左手的左右	---	范围为 100 --- 3763	--- 向右增大，向左减小 --- 中间值 --- 2100
	ADC1的通道14	---	右手的左右	---	范围为 128 --- 4000	--- 向右增大，向左减小 --- 中间值 --- 2210
*/
/* ADC1的通道8的ADC值 */
extern volatile uint32_t ulADC1Channel8Value;
/* ADC1的通道9的ADC值 */
extern volatile uint32_t ulADC1Channel9Value;
/* 采样值是否准备好了 */
extern volatile uint32_t ulIsADC1SampleValueReadyFalg;

void vADC1_Init(void);

// 注意：用作ADC采集的IO必须没有复用，否则采集电压会有影响
/********************ADC3输入通道（引脚）配置**************************/
#define    ADC_APBxClock_FUN             RCC_APB2PeriphClockCmd
#define    ADC_CLK                       RCC_APB2Periph_ADC3//RCC_APB2Periph_ADC1

#define    ADC_GPIO_APBxClock_FUN        RCC_APB2PeriphClockCmd
#define    ADC_GPIO_CLK                  RCC_APB2Periph_GPIOC  
#define    ADC_PORT                      GPIOC

/*以下三行是为移植到新生主板而增加的*/
#define    ADC_GPIO_APBxClock_FUN2        RCC_APB2PeriphClockCmd
#define    ADC_GPIO_CLK2                  RCC_APB2Periph_GPIOF
#define    ADC_PORT2                      GPIOF


// 注意
// 1-PC0 在霸道里面接的是蜂鸣器，默认被拉低
// 2-PC0 在指南者里面接的是SPI FLASH的 片选，默认被拉高
// 所以 PC0 做 ADC 转换通道的时候，结果可能会有误差

// 转换通道个数
#define    NOFCHANEL										 5//6

#define    ADC_PIN1                      GPIO_Pin_0
#define    ADC_CHANNEL1                  ADC_Channel_10

#define    ADC_PIN2                      GPIO_Pin_1
#define    ADC_CHANNEL2                  ADC_Channel_11

#define    ADC_PIN3                      GPIO_Pin_8//GPIO_Pin_2
#define    ADC_CHANNEL3                  ADC_Channel_6//ADC_Channel_12

#define    ADC_PIN4                      GPIO_Pin_9//GPIO_Pin_3
#define    ADC_CHANNEL4                  ADC_Channel_7//ADC_Channel_13

#define    ADC_PIN5                      GPIO_Pin_10//GPIO_Pin_4
#define    ADC_CHANNEL5                  ADC_Channel_8//ADC_Channel_14

#if 0	//因为只在新生主板上只采集五个通道的模拟量，因此第六个通道不使用
#define    ADC_PIN6                      GPIO_Pin_5
#define    ADC_CHANNEL6                  ADC_Channel_15
#endif

// ADC1 对应 DMA1通道1，ADC3对应DMA2通道5，ADC2没有DMA功能
#define    ADC_x                         ADC3//ADC1
#define    ADC_DMA_CHANNEL               DMA2_Channel5//DMA1_Channel1
#define    ADC_DMA_CLK                   RCC_AHBPeriph_DMA2//RCC_AHBPeriph_DMA1


/**************************函数声明********************************/

void adc (void);




#endif 

/* end of file cppyright reserve by team of yanjun ,More information please browse www.yanjuntech.cn */
