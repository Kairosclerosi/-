#ifndef _OLED_H
#define _OLED_H

#include "systick.h"
#include "oled_iic.h"
#include "oled_font.h"

#define FONT_SIZE   16
#define XLevelL			0x00
#define XLevelH			0x10
#define Max_Column	128
#define Max_Row			64
#define	Brightness	0xFF 
#define X_WIDTH 		128
#define Y_WIDTH 		64	

#define OLED_SLAVE_ADDR 0x78

void vOLED_WriteCmd(uint8_t ucI2C_Command);
void vOLED_WriteDat(uint8_t ucI2C_Data);
void vOLED_Init(void);
void vOLED_SetPos(uint8_t ucX, uint8_t ucY);
void vOLED_Fill(uint8_t ucFill_Data);
void vOLED_CLS(void);
void vOLED_ON(void);
void vOLED_OFF(void);
void vOLED_Show(uint8_t ucX, uint8_t ucY, uint8_t *pucCh, uint16_t usSize_sum, uint16_t usSize_x);
void vOLED_ShowChar(uint8_t x,uint8_t y,uint8_t ucChar);
void vOLED_ShowNum(uint8_t x,uint8_t y,uint32_t ulNum,uint8_t ucLength,uint8_t ucSize);
void vOLED_DrawBMP(uint8_t x0, uint8_t y0,uint8_t x1, uint8_t y1,const uint8_t BMP[]);
void vOLED_ShowCHinese(uint8_t x,uint8_t y,uint8_t no);
void vOLED_ShowString(uint8_t x,uint8_t y,uint8_t *pucChar);

#endif










