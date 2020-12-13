#include "oled.h"

void vOLED_WriteCmd(uint8_t ucI2C_Command)				   //��OLEDд��һ������
{
	xOLEDI2C_Write(OLED_SLAVE_ADDR, 0x00, &ucI2C_Command, 1);
}

void vOLED_WriteDat(uint8_t ucI2C_Data)					//��OLEDд��һ������
{
	xOLEDI2C_Write(OLED_SLAVE_ADDR, 0x40, &ucI2C_Data, 1);
}

void vOLED_Init(void)					 //OLED��ʼ��
{
//	vDelayMs(100);
	
	vOLED_WriteCmd(0xAE); //display off
	vOLED_WriteCmd(0x20); //Set Memory Addressing Mode	
	vOLED_WriteCmd(0x10); //00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
	vOLED_WriteCmd(0xb0); //Set Page Start Address for Page Addressing Mode,0-7
	vOLED_WriteCmd(0xc8); //Set COM Output Scan Direction
	vOLED_WriteCmd(0x00); //---set low column address
	vOLED_WriteCmd(0x10); //---set high column address
	vOLED_WriteCmd(0x40); //--set start line address
	vOLED_WriteCmd(0x81); //--set contrast control register
	vOLED_WriteCmd(0xff); //���ȵ��� 0x00~0xff
	vOLED_WriteCmd(0xa1); //--set segment re-map 0 to 127
	vOLED_WriteCmd(0xa6); //--set normal display
	vOLED_WriteCmd(0xa8); //--set multiplex ratio(1 to 64)
	vOLED_WriteCmd(0x3F); //
	vOLED_WriteCmd(0xa4); //0xa4,Output follows RAM content;0xa5,Output ignores RAM content
	vOLED_WriteCmd(0xd3); //-set display offset
	vOLED_WriteCmd(0x00); //-not offset
	vOLED_WriteCmd(0xd5); //--set display clock divide ratio/oscillator frequency
	vOLED_WriteCmd(0xf0); //--set divide ratio
	vOLED_WriteCmd(0xd9); //--set pre-charge period
	vOLED_WriteCmd(0x22); //
	vOLED_WriteCmd(0xda); //--set com pins hardware configuration
	vOLED_WriteCmd(0x12);
	vOLED_WriteCmd(0xdb); //--set vcomh
	vOLED_WriteCmd(0x20); //0x20,0.77xVcc
	vOLED_WriteCmd(0x8d); //--set DC-DC enable
	vOLED_WriteCmd(0x14); //
	vOLED_WriteCmd(0xaf); //--turn on oled panel
}

/*
***********************************************************************
*�������ƣ�void vOLED_SetPos(uint8_t ucX, uint8_t ucY)
*
*�������ܣ���λOLED��ʼ����
*
*ʹ��˵������λOLED��ʾ����ʼ����
*��ڲ�����ucX����ʼx���꣨0-127�� ucY����ʼY���꣨0-7��Y����+1��λ�������ƶ�8�����ص㣩
***********************************************************************
*/
void vOLED_SetPos(uint8_t ucX, uint8_t ucY)
{
	vOLED_WriteCmd(0xb0 + ucY);
	vOLED_WriteCmd(((ucX&0xf0)>>4)|0x10);
	vOLED_WriteCmd((ucX&0x0f)|0x01);
}

/*
***********************************************************************
*�������ƣ�void vOLED_Fill(uint8_t ucFill_Data)
*
*�������ܣ��������OLED��
*
*ʹ��˵������ͬ���������������OLED��
*��ڲ�����ucFill_Data������õ�����
***********************************************************************
*/
void vOLED_Fill(uint8_t ucFill_Data)
{
	uint8_t m, n;
	for(m = 0; m < 8; m++)
	{
		vOLED_WriteCmd(0xb0 + m);
		vOLED_WriteCmd(0x00);
		vOLED_WriteCmd(0x10);
		for(n = 0;n < 128; n++)
		{
			vOLED_WriteDat(ucFill_Data);
		}
	}
}


void vOLED_CLS(void)					//����
{
	vOLED_Fill(0x00);
}


void vOLED_ON(void)				 //��OLED��
{
	vOLED_WriteCmd(0x8D);
	vOLED_WriteCmd(0x14);
	vOLED_WriteCmd(0xAF);
}


void vOLED_OFF(void)			   //�ر�OLED��
{
	vOLED_WriteCmd(0x8D);
	vOLED_WriteCmd(0x10);
	vOLED_WriteCmd(0xAE);
}


void vOLED_Show(uint8_t ucX, uint8_t ucY, uint8_t *pucCh, uint16_t usSize_sum, uint16_t usSize_x)			 //��ʾ���ݺ���
{
	uint8_t i = 0;
	uint8_t j = 0;
	/*һ����ɨ��*/
	for(j = 0; (j < (usSize_sum/usSize_x))&&(j < 8); j++)
	{
		vOLED_SetPos(ucX, ucY + j);	
		/*����һ����ɨ��*/
		for( i = 0; (i < usSize_x)&&(i < 128); i++)
		{
			vOLED_WriteDat(*(pucCh + j * usSize_x + i));
		}
	}
}

void vOLED_ShowChar(uint8_t x,uint8_t y,uint8_t ucChar)
{      	
	uint8_t ucCharVal = 0;
	uint8_t i=0;	
	/* �õ��ַ���ƫ��֮���ֵ */
	ucCharVal = ucChar - ' ';
	/* ������õĳ��Ϳ�Ƚϴ� */
	if(x>Max_Column-1)
	{
		x=0;
		y=y+2;
	}
	if(FONT_SIZE == 16)
	{
		vOLED_SetPos(x,y);	
		for(i=0;i<8;i++)
		{
			vOLED_WriteDat(F8X16[ucCharVal*16+i]);
		}
		vOLED_SetPos(x,y+1);
		for(i=0;i<8;i++)
		{
			vOLED_WriteDat(F8X16[ucCharVal*16+i+8]);
		}
	}else 
	{	
		vOLED_SetPos(x,y+1);
		for(i=0;i<6;i++)
		vOLED_WriteDat(F6x8[ucCharVal][i]);
	}
}

//m^n����
u32 vOLED_Pow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}	

void vOLED_ShowNum(uint8_t x,uint8_t y,uint32_t ulNum,uint8_t ucLength,uint8_t ucSize)
{         	
	uint8_t i = 0;
	uint8_t ucTemp = 0;
	uint8_t enshow = 0;						   
	for(i = 0; i < ucLength;i++)
	{
		ucTemp = (ulNum / vOLED_Pow(10,ucLength - i - 1)) % 10;
		if(enshow == 0 && i <(ucLength - 1))
		{
			if(ucTemp == 0)
			{
				vOLED_ShowChar(x+(ucSize / 2) * i ,y,' ');
				continue;
			}else 
			{
				enshow=1; 
			}
		 	 
		}
	 	vOLED_ShowChar(x+(ucSize / 2) * i,y,ucTemp+'0'); 
	}
} 

//��ʾһ���ַ��Ŵ�
void vOLED_ShowString(uint8_t x,uint8_t y,uint8_t *pucChar)
{
	uint8_t j=0;
	while (pucChar[j]!='\0')
	{		
		vOLED_ShowChar(x,y,pucChar[j]);
		x += 8;
		if(x>120)
		{
			x=0;
			y+=2;
		}
		j++;
	}
}


void vOLED_DrawBMP(uint8_t x0, uint8_t y0,uint8_t x1, uint8_t y1,const uint8_t BMP[])			  //��ʾBMPͼƬ
{ 	
	uint32_t j = 0;
	uint8_t x = 0;
	uint8_t y = 0;
  
  if(y1 % 8 == 0)
	{	
		y = y1 / 8;
	}else
	{	
		y=y1 / 8 + 1;
	}
	for(y=y0;y<y1;y++)
	{
		vOLED_SetPos(x0,y);
		for(x=x0;x<x1;x++)
		{      
			vOLED_WriteDat(BMP[j++]);	   
		}
	}
} 

void vOLED_ShowCHinese(uint8_t x,uint8_t y,uint8_t no)
{      			    
	uint8_t t = 0;
	uint8_t adder = 0;
	vOLED_SetPos(x,y);	
  for(t = 0;t < 16;t++)
	{
		vOLED_WriteDat(Hzk[2*no][t]);
		adder += 1;
  }	
	vOLED_SetPos(x,y+1);	
	for(t = 0;t < 16;t++)
	{	
		vOLED_WriteDat(Hzk[2*no+1][t]);
		adder += 1;
	}					
}

/* end of file cppyright reserve by team of Happy Fish */
