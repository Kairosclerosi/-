#ifndef _OLED_IIC_H
#define _OLED_IIC_H

#include "system.h"
#include "systick.h"

/* IIC_SCL */
#define OLED_GPIO_PORT_IIC_SCL			GPIOB
#define OLED_GPIO_PIN_IIC_SCL			GPIO_Pin_6
#define OLED_RCC_IIC_SCL						RCC_APB2Periph_GPIOB
/* IIC_SDA */
#define OLED_GPIO_PORT_IIC_SDA			GPIOB
#define OLED_GPIO_PIN_IIC_SDA			GPIO_Pin_7
#define OLED_RCC_IIC_SDA						RCC_APB2Periph_GPIOB


#define vOLEDI2CDelay() {__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();}
/***
*因为软件IIC，要改变IO 口的读写方向，这里给出定义,要修改IO口的时候，这个地方也要同时修改
*
*/
// /* PB10 作为SCL时，PB11作为SDA时 */
// #define I2C_SDA_IN()  	{GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH |= 8<<12;}
// #define I2C_SDA_OUT() 	{GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH |= 3<<12;}

/* 如果 PB7为 SDA PB6为SCL  */
#define OLED_I2C_SDA_IN()  {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=(u32)8<<28;} 
#define OLED_I2C_SDA_OUT() {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=(u32)3<<28;}

// /* PB7 SCL PB6 SDA */
// #define OLED_I2C_SDA_IN()  {GPIOB->CRL&=0XF0FFFFFF;GPIOB->CRL|=(u32)8<<24;} 
// #define OLED_I2C_SDA_OUT() {GPIOB->CRL&=0XF0FFFFFF;GPIOB->CRL|=(u32)3<<24;}
/*  */


/**
*定义IIC的IO 口直接操作的位带操作宏定义,要修改IO口的时候，这个地方也要同时修改
*
*/

/* SCL写 */
#define OLED_I2C_SCL    						PBout(6) 
/* SDA写 */
#define OLED_I2C_SDA    						PBout(7) 
/* SDA读 */
#define OLED_I2C_READ_SDA   				PBin(7)  

/* 在IIC读取ACK的时候的等待次数 */
#define OLED_ANALOG_IIC_WAIT_ACK_TIMES			((uint32_t)250)

void vOLEDI2C_Init(void);
ErrorStatus xOLEDI2C_Write(uint8_t ucI2cSlaveAddr, uint8_t ucRegAddr, uint8_t * pucBuffer, uint32_t ulLength);
ErrorStatus xOLEDI2C_Read(uint8_t ucI2cSlaveAddr, uint8_t ucRegAddr, uint8_t * pucBuffer, uint32_t ulLength);
ErrorStatus xOLEDI2C_CheckDevice(uint8_t ucI2cSlaveAddr);

#endif

