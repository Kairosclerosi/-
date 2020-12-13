#ifndef _ADC1_H
#define	_ADC1_H

#include "system.h"

/* ADC1��ͨ������ */
#define ADC1_CHANNEL_NUMBER	((uint32_t)2)

/* ADC1�������鳤�� ���ܹ���4��ͨ��������Ƶ��Ϊ 50KHZ */
//#define NOFCHANEL 							((uint32_t)200)
#define ADC1_SAMPLE_NUM_ONE_CHANNEL 	((uint32_t)NOFCHANEL/ADC1_CHANNEL_NUMBER)

/* ADC1���ݼĴ�����ַ */
#define ADC1_DR_Address    ((uint32_t)0x40012400+0x4c)

/*
	����˵����ÿ��ͨ������Ӧ�ĺ���
	ADC1��ͨ��4	---	���ֵ�����	---	��ΧΪ 0 --- 4092	--- �����������¼�С --- �м�ֵ --- 2010 +- 50
	ADC1��ͨ��8	---	���ֵ�΢��	---	��ΧΪ 0 --- 4095	--- ˳ʱ���С����ʱ������ --- �м�ֵ --- 2000����
	ADC1��ͨ��9	---	���ֵ�΢��	---	��ΧΪ 0 --- 4094	--- ˳ʱ���С����ʱ������ --- �м�ֵ --- 2000����
	ADC1��ͨ��12	---	���ֵ�����	---	��ΧΪ140 ---4095	--- �����������¼�С --- �м�ֵ --- 2000����
	ADC1��ͨ��13	---	���ֵ�����	---	��ΧΪ 100 --- 3763	--- �������������С --- �м�ֵ --- 2100
	ADC1��ͨ��14	---	���ֵ�����	---	��ΧΪ 128 --- 4000	--- �������������С --- �м�ֵ --- 2210
*/
/* ADC1��ͨ��8��ADCֵ */
extern volatile uint32_t ulADC1Channel8Value;
/* ADC1��ͨ��9��ADCֵ */
extern volatile uint32_t ulADC1Channel9Value;
/* ����ֵ�Ƿ�׼������ */
extern volatile uint32_t ulIsADC1SampleValueReadyFalg;

void vADC1_Init(void);

// ע�⣺����ADC�ɼ���IO����û�и��ã�����ɼ���ѹ����Ӱ��
/********************ADC3����ͨ�������ţ�����**************************/
#define    ADC_APBxClock_FUN             RCC_APB2PeriphClockCmd
#define    ADC_CLK                       RCC_APB2Periph_ADC3//RCC_APB2Periph_ADC1

#define    ADC_GPIO_APBxClock_FUN        RCC_APB2PeriphClockCmd
#define    ADC_GPIO_CLK                  RCC_APB2Periph_GPIOC  
#define    ADC_PORT                      GPIOC

/*����������Ϊ��ֲ��������������ӵ�*/
#define    ADC_GPIO_APBxClock_FUN2        RCC_APB2PeriphClockCmd
#define    ADC_GPIO_CLK2                  RCC_APB2Periph_GPIOF
#define    ADC_PORT2                      GPIOF


// ע��
// 1-PC0 �ڰԵ�����ӵ��Ƿ�������Ĭ�ϱ�����
// 2-PC0 ��ָ��������ӵ���SPI FLASH�� Ƭѡ��Ĭ�ϱ�����
// ���� PC0 �� ADC ת��ͨ����ʱ�򣬽�����ܻ������

// ת��ͨ������
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

#if 0	//��Ϊֻ������������ֻ�ɼ����ͨ����ģ��������˵�����ͨ����ʹ��
#define    ADC_PIN6                      GPIO_Pin_5
#define    ADC_CHANNEL6                  ADC_Channel_15
#endif

// ADC1 ��Ӧ DMA1ͨ��1��ADC3��ӦDMA2ͨ��5��ADC2û��DMA����
#define    ADC_x                         ADC3//ADC1
#define    ADC_DMA_CHANNEL               DMA2_Channel5//DMA1_Channel1
#define    ADC_DMA_CLK                   RCC_AHBPeriph_DMA2//RCC_AHBPeriph_DMA1


/**************************��������********************************/

void adc (void);




#endif 

/* end of file cppyright reserve by team of yanjun ,More information please browse www.yanjuntech.cn */
