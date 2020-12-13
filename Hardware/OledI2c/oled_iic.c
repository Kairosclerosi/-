/*
***********************************************************************
* 文件名称：soft_iic.c soft_iic.h
* 文件摘要：软件模拟的iic通信协议代码
***********************************************************************
*/

#include "oled_iic.h"

void vOLEDI2C_Init(void)					//软件IIC初始化，初始化两个IO口作为软件模拟IIC的SCL,SDA
{					     
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/* 开启时钟 */
	RCC_APB2PeriphClockCmd(OLED_RCC_IIC_SCL|OLED_RCC_IIC_SDA, ENABLE); 
						
	/* 初始化IO口 PB10 作为 软件模拟IIC 的 IIC_SCL */
	GPIO_InitStructure.GPIO_Pin = OLED_GPIO_PIN_IIC_SCL;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(OLED_GPIO_PORT_IIC_SCL, &GPIO_InitStructure); 		
	
	/* 初始化IO口 PB11 作为 软件模拟IIC 的 IIC_SDA */
	GPIO_InitStructure.GPIO_Pin = OLED_GPIO_PIN_IIC_SDA;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(OLED_GPIO_PORT_IIC_SDA, &GPIO_InitStructure); 	

	/* 默认拉高IIC总线 */
	GPIO_SetBits(OLED_GPIO_PORT_IIC_SDA, OLED_GPIO_PIN_IIC_SCL|OLED_GPIO_PIN_IIC_SDA);
}

void vOLEDI2C_Start(void)		  //软件IIC产生起始
{
	/* IIC_SDA 方向选择输出 */
	OLED_I2C_SDA_OUT();          

	/* 先拉高IIC总线 */
	OLED_I2C_SDA = 1;	  	  
	OLED_I2C_SCL = 1;
	/* 延时 4US */
	vOLEDI2CDelay();
	/* 在SCL为高电平的时候 SDA 产生一个下降沿 */
 	OLED_I2C_SDA = 0;         
	/* 延时 4US */
	vOLEDI2CDelay();
	/* 拉低SCL 准备进行发送数据 */
	/* 每一个函数出去之前，都保证SCL是低电平 */
	OLED_I2C_SCL = 0;          
}	

void vOLEDI2C_Stop(void)					  //软件IIC产生停止位的函数
{
	/* IIC_SDA 方向选择输出 */
	OLED_I2C_SDA_OUT();      
	
	/* 先拉低IIC总线 */
	OLED_I2C_SCL = 0;
	OLED_I2C_SDA = 0; 
	/* 延时 4US */
 	vOLEDI2CDelay();
	/* 在SCL为高电平的时候 SDA 产生一个上升沿 */
	OLED_I2C_SCL = 1; 
	/* 延时 4US */
	vOLEDI2CDelay();
	/* SDA产生上升沿 */
	OLED_I2C_SDA = 1;  
	/* 软件延时 */
	vOLEDI2CDelay();			
	/* 这个函数把IIC时序结束了所以SCL是高电平 */
}


ErrorStatus xOLEDI2C_WaitAck(uint32_t ulDelayTimes)				  //等待IIC器件回复ACK
{
	/* IIC_SDA 方向选择输入 */
	OLED_I2C_SDA_IN();    
	/*  */
	OLED_I2C_SDA = 1;             
	vOLEDI2CDelay();	 
	/* 拉高SCL 开始读取SDA数据 */
	OLED_I2C_SCL = 1;
	vOLEDI2CDelay();
	/* 读取SDA是否有ACK */
	while(OLED_I2C_READ_SDA)         
	{
		if(ulDelayTimes-- == 0)
		{
			/* 发生超时错误 */
			vOLEDI2C_Stop();
			return ERROR;  
		}
	}
	/* 每一个函数出去之前，都保证SCL是低电平 */
	OLED_I2C_SCL = 0;              	   
	return SUCCESS;  
} 

void vOLEDI2C_Ack(void)						 //等待IIC器件回复ACK
{
	/* 拉低SCL准备 向SDA线上发送数据 */
	OLED_I2C_SCL = 0;
	/* OLED_I2C_SDA_OUT 这个改变SDA方向的语句不能修改在程序中的顺序 */
	OLED_I2C_SDA_OUT();
	/* 在SDA上发送 ACK */
	OLED_I2C_SDA = 0;
	/* 软件延时 */
	vOLEDI2CDelay();
	/* 拉高SCL 让别人读取 SDA 上的数据 */
	OLED_I2C_SCL = 1;
	/* 软件延时 */
	vOLEDI2CDelay();
	/* 每一个函数出去之前，都保证SCL是低电平 */
	OLED_I2C_SCL = 0;
}

void vOLEDI2C_NAck(void)					 //产生Nack应答信号
{
	/* 拉低SCL准备 向SDA线上发送数据 */
	OLED_I2C_SCL = 0;
	/* OLED_I2C_SDA_OUT 这个改变SDA方向的语句不能修改在程序中的顺序 */
	OLED_I2C_SDA_OUT();
	/* 在SDA上发送 NACK */
	OLED_I2C_SDA = 1;
	/* 软件延时 */
	vOLEDI2CDelay();
	/* 拉高SCL 让别人读取 SDA 上的数据 */
	OLED_I2C_SCL = 1;
	/* 软件延时 */
	vOLEDI2CDelay();
	/* 每一个函数出去之前，都保证SCL是低电平 */
	OLED_I2C_SCL = 0;
}

void vOLEDI2C_SendByte(uint8_t ucData)					  //在IIC总线上发送一个字节
{   
	uint8_t ucMask = 0;                              
	/* 选择SDA方向为输出 */
	OLED_I2C_SDA_OUT();  
							  
	for(ucMask = 0x80; ucMask != 0; ucMask >>= 1)       
	{
		if((ucMask & ucData) == 0)              
		{
			OLED_I2C_SDA = 0;
		}else
		{
			OLED_I2C_SDA = 1;
		}
		vOLEDI2CDelay();
		OLED_I2C_SCL = 1;                       
		vOLEDI2CDelay();
		OLED_I2C_SCL = 0;                       
		vOLEDI2CDelay();
	}
}

uint8_t ucOLEDI2C_RecvByte(uint8_t ucIsNeedAck)				//在IIC总线上接收一个字节
{
	uint8_t ucMask = 0;
	uint8_t ucReceive = 0;
	/* IIC_SDA 方向选择输 */
	OLED_I2C_SDA_IN();                              
	/* 先接收高字节 */
	for(ucMask = 0x80; ucMask != 0; ucMask >>= 1)
	{
		/* 给出SCL时钟 */
		OLED_I2C_SCL=0; 
		vOLEDI2CDelay();
		OLED_I2C_SCL=1;
		/* 读取SDA线上的数据 */
		if(OLED_I2C_READ_SDA)
		{
			ucReceive |= ucMask;
		}			
		vOLEDI2CDelay(); 
	}					 
	if (ucIsNeedAck)
	{
		vOLEDI2C_Ack();                         
	}else
	{
		vOLEDI2C_NAck();
	}
	
	return ucReceive;
}

/*
**********************************************************************
*函数名称：ErrorStatus xOLEDI2C_Write(uint8_t ucI2cSlaveAddr, uint8_t ucRegAddr, 
*																	uint8_t * pucBuffer, uint32_t ulLength)
*
*
*函数功能：用IIC总线写数据
*入口参数：
*					IicSlaveAddr:IIC器件地址
*					regAddr			:寄存器地址
*					buffer			:缓冲区指针
*					length			:发送数据长度
*返 回 值：是否错误
**********************************************************************
*/

ErrorStatus xOLEDI2C_Write(uint8_t ucI2cSlaveAddr, uint8_t ucRegAddr, uint8_t * pucBuffer, uint32_t ulLength)
{
	vOLEDI2C_Start();
	vOLEDI2C_SendByte(ucI2cSlaveAddr);
	if(xOLEDI2C_WaitAck(OLED_ANALOG_IIC_WAIT_ACK_TIMES) == ERROR)
	{
		return ERROR;
	}
	vOLEDI2C_SendByte(ucRegAddr);
	if(xOLEDI2C_WaitAck(OLED_ANALOG_IIC_WAIT_ACK_TIMES) == ERROR)
	{
		return ERROR;
	} 
	
	while(ulLength--)
	{
		vOLEDI2C_SendByte(*pucBuffer++);
		if(xOLEDI2C_WaitAck(OLED_ANALOG_IIC_WAIT_ACK_TIMES) == ERROR)
		{
			return ERROR;
		} 
	}
	
	vOLEDI2C_Stop();
	return SUCCESS;
}

/*
**********************************************************************
*函数名称：ErrorStatus xOLEDI2C_Read(uint8_t ucI2cSlaveAddr, uint8_t ucRegAddr, 
*																uint8_t * pucBuffer, uint32_t ulLength)
*
*函数功能：用IIC总线读取数据
*入口参数：IicSlaveAddr:IIC器件地址
*					regAddr			:寄存器地址
*					buffer			:缓冲区指针
*					length			:发送数据长度
*返 回 值：是否错误
**********************************************************************
*/

ErrorStatus xOLEDI2C_Read(uint8_t ucI2cSlaveAddr, uint8_t ucRegAddr, uint8_t * pucBuffer, uint32_t ulLength)
{
	vOLEDI2C_Start();

	vOLEDI2C_SendByte(ucI2cSlaveAddr); 

	if(xOLEDI2C_WaitAck(OLED_ANALOG_IIC_WAIT_ACK_TIMES) == ERROR)
	{
		return ERROR;
	}
	vOLEDI2C_SendByte(ucRegAddr);       
	if(xOLEDI2C_WaitAck(OLED_ANALOG_IIC_WAIT_ACK_TIMES) == ERROR)
	{
		return ERROR;
	}
	vOLEDI2C_Start();
	vOLEDI2C_SendByte(ucI2cSlaveAddr+1);
	if(xOLEDI2C_WaitAck(OLED_ANALOG_IIC_WAIT_ACK_TIMES) == ERROR)
	{
		return ERROR;
	}

	/* 开始接受数据 */
	/* 这样做是因为最后一个读取的数据要给出NACK */
	ulLength--;
	while(ulLength--)
	{
		/* 不是最后一个给出ACK */
		*pucBuffer++ = ucOLEDI2C_RecvByte(1);
	}

	/* 最后一个给出NACK */
	*pucBuffer = ucOLEDI2C_RecvByte(0);

	vOLEDI2C_Stop();	
	return SUCCESS;
}

/*
**********************************************************************
*函数名称：ErrorStatus vOLEDI2C_CheckDevice(uint8_t IicSlaveAddr)
*
*函数功能：检查IIC总线上是否有相应地址的器件
**********************************************************************
*/

ErrorStatus xOLEDI2C_CheckDevice(uint8_t ucI2cSlaveAddr)
{
  ErrorStatus ack;
	
	/* 产生起始位 */
	vOLEDI2C_Start();
	/* 发送IIC器件地址 方向上选择 写 ， 0 代表写 1 代表 读  */
	vOLEDI2C_SendByte(ucI2cSlaveAddr);
	/* 等待ACK */
	ack = xOLEDI2C_WaitAck(OLED_ANALOG_IIC_WAIT_ACK_TIMES);
	/* 产生停止位 */
	vOLEDI2C_Stop();
	
	return ack;
}

/* end of file cppyright reserve by team of yanjun More information please browse www.yanjuntech.cn */
