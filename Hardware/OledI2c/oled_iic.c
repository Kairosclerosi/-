/*
***********************************************************************
* �ļ����ƣ�soft_iic.c soft_iic.h
* �ļ�ժҪ�����ģ���iicͨ��Э�����
***********************************************************************
*/

#include "oled_iic.h"

void vOLEDI2C_Init(void)					//���IIC��ʼ������ʼ������IO����Ϊ���ģ��IIC��SCL,SDA
{					     
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/* ����ʱ�� */
	RCC_APB2PeriphClockCmd(OLED_RCC_IIC_SCL|OLED_RCC_IIC_SDA, ENABLE); 
						
	/* ��ʼ��IO�� PB10 ��Ϊ ���ģ��IIC �� IIC_SCL */
	GPIO_InitStructure.GPIO_Pin = OLED_GPIO_PIN_IIC_SCL;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(OLED_GPIO_PORT_IIC_SCL, &GPIO_InitStructure); 		
	
	/* ��ʼ��IO�� PB11 ��Ϊ ���ģ��IIC �� IIC_SDA */
	GPIO_InitStructure.GPIO_Pin = OLED_GPIO_PIN_IIC_SDA;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(OLED_GPIO_PORT_IIC_SDA, &GPIO_InitStructure); 	

	/* Ĭ������IIC���� */
	GPIO_SetBits(OLED_GPIO_PORT_IIC_SDA, OLED_GPIO_PIN_IIC_SCL|OLED_GPIO_PIN_IIC_SDA);
}

void vOLEDI2C_Start(void)		  //���IIC������ʼ
{
	/* IIC_SDA ����ѡ����� */
	OLED_I2C_SDA_OUT();          

	/* ������IIC���� */
	OLED_I2C_SDA = 1;	  	  
	OLED_I2C_SCL = 1;
	/* ��ʱ 4US */
	vOLEDI2CDelay();
	/* ��SCLΪ�ߵ�ƽ��ʱ�� SDA ����һ���½��� */
 	OLED_I2C_SDA = 0;         
	/* ��ʱ 4US */
	vOLEDI2CDelay();
	/* ����SCL ׼�����з������� */
	/* ÿһ��������ȥ֮ǰ������֤SCL�ǵ͵�ƽ */
	OLED_I2C_SCL = 0;          
}	

void vOLEDI2C_Stop(void)					  //���IIC����ֹͣλ�ĺ���
{
	/* IIC_SDA ����ѡ����� */
	OLED_I2C_SDA_OUT();      
	
	/* ������IIC���� */
	OLED_I2C_SCL = 0;
	OLED_I2C_SDA = 0; 
	/* ��ʱ 4US */
 	vOLEDI2CDelay();
	/* ��SCLΪ�ߵ�ƽ��ʱ�� SDA ����һ�������� */
	OLED_I2C_SCL = 1; 
	/* ��ʱ 4US */
	vOLEDI2CDelay();
	/* SDA���������� */
	OLED_I2C_SDA = 1;  
	/* �����ʱ */
	vOLEDI2CDelay();			
	/* ���������IICʱ�����������SCL�Ǹߵ�ƽ */
}


ErrorStatus xOLEDI2C_WaitAck(uint32_t ulDelayTimes)				  //�ȴ�IIC�����ظ�ACK
{
	/* IIC_SDA ����ѡ������ */
	OLED_I2C_SDA_IN();    
	/*  */
	OLED_I2C_SDA = 1;             
	vOLEDI2CDelay();	 
	/* ����SCL ��ʼ��ȡSDA���� */
	OLED_I2C_SCL = 1;
	vOLEDI2CDelay();
	/* ��ȡSDA�Ƿ���ACK */
	while(OLED_I2C_READ_SDA)         
	{
		if(ulDelayTimes-- == 0)
		{
			/* ������ʱ���� */
			vOLEDI2C_Stop();
			return ERROR;  
		}
	}
	/* ÿһ��������ȥ֮ǰ������֤SCL�ǵ͵�ƽ */
	OLED_I2C_SCL = 0;              	   
	return SUCCESS;  
} 

void vOLEDI2C_Ack(void)						 //�ȴ�IIC�����ظ�ACK
{
	/* ����SCL׼�� ��SDA���Ϸ������� */
	OLED_I2C_SCL = 0;
	/* OLED_I2C_SDA_OUT ����ı�SDA�������䲻���޸��ڳ����е�˳�� */
	OLED_I2C_SDA_OUT();
	/* ��SDA�Ϸ��� ACK */
	OLED_I2C_SDA = 0;
	/* �����ʱ */
	vOLEDI2CDelay();
	/* ����SCL �ñ��˶�ȡ SDA �ϵ����� */
	OLED_I2C_SCL = 1;
	/* �����ʱ */
	vOLEDI2CDelay();
	/* ÿһ��������ȥ֮ǰ������֤SCL�ǵ͵�ƽ */
	OLED_I2C_SCL = 0;
}

void vOLEDI2C_NAck(void)					 //����NackӦ���ź�
{
	/* ����SCL׼�� ��SDA���Ϸ������� */
	OLED_I2C_SCL = 0;
	/* OLED_I2C_SDA_OUT ����ı�SDA�������䲻���޸��ڳ����е�˳�� */
	OLED_I2C_SDA_OUT();
	/* ��SDA�Ϸ��� NACK */
	OLED_I2C_SDA = 1;
	/* �����ʱ */
	vOLEDI2CDelay();
	/* ����SCL �ñ��˶�ȡ SDA �ϵ����� */
	OLED_I2C_SCL = 1;
	/* �����ʱ */
	vOLEDI2CDelay();
	/* ÿһ��������ȥ֮ǰ������֤SCL�ǵ͵�ƽ */
	OLED_I2C_SCL = 0;
}

void vOLEDI2C_SendByte(uint8_t ucData)					  //��IIC�����Ϸ���һ���ֽ�
{   
	uint8_t ucMask = 0;                              
	/* ѡ��SDA����Ϊ��� */
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

uint8_t ucOLEDI2C_RecvByte(uint8_t ucIsNeedAck)				//��IIC�����Ͻ���һ���ֽ�
{
	uint8_t ucMask = 0;
	uint8_t ucReceive = 0;
	/* IIC_SDA ����ѡ���� */
	OLED_I2C_SDA_IN();                              
	/* �Ƚ��ո��ֽ� */
	for(ucMask = 0x80; ucMask != 0; ucMask >>= 1)
	{
		/* ����SCLʱ�� */
		OLED_I2C_SCL=0; 
		vOLEDI2CDelay();
		OLED_I2C_SCL=1;
		/* ��ȡSDA���ϵ����� */
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
*�������ƣ�ErrorStatus xOLEDI2C_Write(uint8_t ucI2cSlaveAddr, uint8_t ucRegAddr, 
*																	uint8_t * pucBuffer, uint32_t ulLength)
*
*
*�������ܣ���IIC����д����
*��ڲ�����
*					IicSlaveAddr:IIC������ַ
*					regAddr			:�Ĵ�����ַ
*					buffer			:������ָ��
*					length			:�������ݳ���
*�� �� ֵ���Ƿ����
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
*�������ƣ�ErrorStatus xOLEDI2C_Read(uint8_t ucI2cSlaveAddr, uint8_t ucRegAddr, 
*																uint8_t * pucBuffer, uint32_t ulLength)
*
*�������ܣ���IIC���߶�ȡ����
*��ڲ�����IicSlaveAddr:IIC������ַ
*					regAddr			:�Ĵ�����ַ
*					buffer			:������ָ��
*					length			:�������ݳ���
*�� �� ֵ���Ƿ����
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

	/* ��ʼ�������� */
	/* ����������Ϊ���һ����ȡ������Ҫ����NACK */
	ulLength--;
	while(ulLength--)
	{
		/* �������һ������ACK */
		*pucBuffer++ = ucOLEDI2C_RecvByte(1);
	}

	/* ���һ������NACK */
	*pucBuffer = ucOLEDI2C_RecvByte(0);

	vOLEDI2C_Stop();	
	return SUCCESS;
}

/*
**********************************************************************
*�������ƣ�ErrorStatus vOLEDI2C_CheckDevice(uint8_t IicSlaveAddr)
*
*�������ܣ����IIC�������Ƿ�����Ӧ��ַ������
**********************************************************************
*/

ErrorStatus xOLEDI2C_CheckDevice(uint8_t ucI2cSlaveAddr)
{
  ErrorStatus ack;
	
	/* ������ʼλ */
	vOLEDI2C_Start();
	/* ����IIC������ַ ������ѡ�� д �� 0 ����д 1 ���� ��  */
	vOLEDI2C_SendByte(ucI2cSlaveAddr);
	/* �ȴ�ACK */
	ack = xOLEDI2C_WaitAck(OLED_ANALOG_IIC_WAIT_ACK_TIMES);
	/* ����ֹͣλ */
	vOLEDI2C_Stop();
	
	return ack;
}

/* end of file cppyright reserve by team of yanjun More information please browse www.yanjuntech.cn */
