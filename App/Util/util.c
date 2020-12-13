#include "util.h"
#include "usart1_dma.h"

/*
***********************************************************************
*函数名称：ErrorStatus vCompareString(uint8_t * src, uint8_t * des, uint32_t length)
*
*函数功能：比较两个字符串是否相同
*
*使用说明：无
*入口参数：pucSrc:字符串1
					pucDes：字符串2
					ulLength：要比较的长度
*返 回 值：无
***********************************************************************
*/

ErrorStatus vCompareString(uint8_t * pucSrc, uint8_t * pucDes, uint32_t ulLength)
{
	while(ulLength--)
	{
		if(*pucSrc++ != *pucDes++)
		{
			return ERROR;  
		}
	}
	
	return SUCCESS;
}

/*
***********************************************************************
*函数名称：ErrorStatus vDebugSendString(uint8_t * pucBuffer, uint32_t ulSize, uint32_t ulIsNeedCopyData) 
*
*函数功能：发送字符串函数，这是对底层的封装
*
*使用说明：无
*入口参数：pucBuffer:要发送的字符串指针
					ulSize：要发送字符串的长度
					ulIsNeedCopyData：是否需要复制字符串到内存缓冲区中
*返 回 值：是否调用错误
***********************************************************************
*/

ErrorStatus vDebugSendString(uint8_t * pucBuffer, uint32_t ulSize, uint32_t ulIsNeedCopyData) 
{
	return vUSART1_DmaTxStart(pucBuffer, ulSize, ulIsNeedCopyData); 
}

/*
***********************************************************************
*函数名称：ErrorStatus vDebugSendUlNumber(uint32_t ulSendNumber, uint32_t ulInNeedNewLine) 
*
*函数功能：发送无符号的32位正数
*
*使用说明：输入的数必须是正数
*入口参数：ulSendNumber：要发送的数字
					ulInNeedNewLine：是否需要换行
*返 回 值：是否操作成功
***********************************************************************
*/

ErrorStatus vDebugSendUlNumber(uint32_t ulSendNumber, uint32_t ulInNeedNewLine) 
{
	uint8_t ucBuffer[20];
	uint8_t ucString[20];       
	uint32_t ulBufferIndex = 0, ulStringIndex = 0;
	
	/* 判断要发送的数据是不是零 */
	if(ulSendNumber)
	{
		/* 循环把数据取出来 */
		while(ulSendNumber)
		{
			/* 把最末尾的数，取出来 */
			ucBuffer[ulBufferIndex++] = (uint8_t)((ulSendNumber % 10) + '0');
			/* 移出去最后一位 */
			ulSendNumber /= 10;
		}
		
		ulBufferIndex--;
		
		/* 循环交换顺序 */
		while(ulBufferIndex)
		{
			ucString[ulStringIndex++] = ucBuffer[ulBufferIndex--];
		}
		
		/* 注意最后一个字符 */
		ucString[ulStringIndex++] = ucBuffer[ulBufferIndex];
	}else
	{
		/* 要发送的数据是0 */
		ucString[ulStringIndex++] = '0';
	}
	
	if(ulInNeedNewLine)
	{
		ucString[ulStringIndex++] = '\r';
		ucString[ulStringIndex++] = '\n';
	}
	
	/* 发送字符串 */
	return vDebugSendString(ucString, ulStringIndex, 1);
}

/*
***********************************************************************
*函数名称：ErrorStatus vDebugSendUlNumberWithId(uint32_t ulSendNumber, uint8_t ucId, uint32_t ulInNeedNewLine) 
*
*函数功能：发送正数数字，并且在数字前面加上一个ID
*
*使用说明：数字必须是正数
*入口参数：ulSendNumber：要发送的正数
					ucId：数字前面的ID
					ulInNeedNewLine：是否需要换行
*返 回 值：是否操作成功
***********************************************************************
*/

ErrorStatus vDebugSendUlNumberWithId(uint32_t ulSendNumber, uint8_t ucId, uint32_t ulInNeedNewLine) 
{
	uint8_t ucBuffer[20];
	uint8_t ucString[20];       
	uint32_t ulBufferIndex = 0, ulStringIndex = 0;
	
	/* 判断要发送的数据是不是零 */
	if(ulSendNumber)
	{
		/* 循环把数据取出来 */
		while(ulSendNumber)
		{
			/* 把最末尾的数，取出来 */
			ucBuffer[ulBufferIndex++] = (uint8_t)((ulSendNumber % 10) + '0');
			/* 移出去最后一位 */
			ulSendNumber /= 10;
		}
		
		ulBufferIndex--;
		
		/* 在开头加上数字的ID */
		ucString[ulStringIndex++] = ucId;   
		
		/* 循环交换顺序 */
		while(ulBufferIndex)
		{
			ucString[ulStringIndex++] = ucBuffer[ulBufferIndex--];
		}
		
		/* 注意最后一个字符 */
		ucString[ulStringIndex++] = ucBuffer[ulBufferIndex];
	}else
	{
		/* 要发送的数据是0 */
		ucString[ulStringIndex++] = '0';
	}
	
	if(ulInNeedNewLine)
	{
		ucString[ulStringIndex++] = '\r';
		ucString[ulStringIndex++] = '\n';
	}
	
	/* 发送字符串 */
	return vDebugSendString(ucString, ulStringIndex, 1);
}

/*
***********************************************************************
*函数名称：ErrorStatus vDebugSendUlArray(uint32_t * ulSendArray, uint32_t ulArrayLength, uint32_t ulInNeedNewLine) 
*
*函数功能：发送正数数组
*
*使用说明：发送的都是正数
*入口参数：ulSendArray：数组指针
					ulArrayLength：要发送数组的长度
					ulInNeedNewLine：是否在发送的时候进行换行
*返 回 值：是否操作成功
***********************************************************************
*/

ErrorStatus vDebugSendUlArray(uint32_t * ulSendArray, uint32_t ulArrayLength, uint32_t ulInNeedNewLine) 
{
	uint8_t ucBuffer[20];
	uint8_t ucString[200]; 
	uint32_t ulBufferIndex = 0, ulStringIndex = 0;
	
	/* 循环取出来每一个数 */
	while(ulArrayLength--)
	{
		/* 先要清零缓冲区索引值,这个缓冲区是循环利用的 */
		ulBufferIndex = 0;
		/* 判断要发送的数据是不是零 */
		if(*ulSendArray)
		{
			/* 循环把数据取出来 */
			while(*ulSendArray)
			{
				/* 把最末尾的数，取出来 */
				ucBuffer[ulBufferIndex++] = (uint8_t)(((*ulSendArray) % 10) + '0');
				/* 移出去最后一位 */
				(*ulSendArray) /= 10; 
			}
			
			ulBufferIndex--;
			
			/* 循环交换顺序 */
			while(ulBufferIndex)
			{
				ucString[ulStringIndex++] = ucBuffer[ulBufferIndex--];
			}
			
			/* 注意最后一个字符 */
			ucString[ulStringIndex++] = ucBuffer[ulBufferIndex];
		}else
		{
			/* 要发送的数据是0 */
			ucString[ulStringIndex++] = '0';
		}
		
		if(ulInNeedNewLine)
		{
			ucString[ulStringIndex++] = '\r';
			ucString[ulStringIndex++] = '\n';
		}	
		/* 指向下一个数字 */
		ulSendArray++; 
	}
	
	/* 发送字符串 */
	return vDebugSendString(ucString, ulStringIndex, 1);
}

/*
***********************************************************************
*函数名称：ErrorStatus vDebugSendUlArrayWithId(uint32_t * ulSendArray, uint8_t * pucId, uint32_t ulArrayLength, uint32_t ulInNeedNewLine) 
*
*函数功能：发送正数数组，并且在每个数字前面加上ID
*
*使用说明：发送的都是正数
					在函数里面不会进行数组越界检查，所以需要自己保证数组不会越界
*入口参数：ulSendArray：发送的数组指针
					pucId：每个数字前面的ID
					ulArrayLength：要发送的数组长度
					ulInNeedNewLine：时候再发送的时候进行换行
*返 回 值：是否操作成功
***********************************************************************
*/

ErrorStatus vDebugSendUlArrayWithId(uint32_t * ulSendArray, uint8_t * pucId, uint32_t ulArrayLength, uint32_t ulInNeedNewLine) 
{
	uint8_t ucBuffer[20];
	uint8_t ucString[200]; 
	uint32_t ulBufferIndex = 0, ulStringIndex = 0;
	
	/* 循环取出来每一个数 */
	while(ulArrayLength--)
	{
		/* 先要清零缓冲区索引值,这个缓冲区是循环利用的 */
		ulBufferIndex = 0;
		/* 判断要发送的数据是不是零 */
		if(*ulSendArray)
		{
			/* 循环把数据取出来 */
			while(*ulSendArray)
			{
				/* 把最末尾的数，取出来 */
				ucBuffer[ulBufferIndex++] = (uint8_t)(((*ulSendArray) % 10) + '0');
				/* 移出去最后一位 */
				(*ulSendArray) /= 10; 
			}
			
			ulBufferIndex--;
			
			/* 在开头加上数字的ID */
			ucString[ulStringIndex++] = *pucId++;
			
			/* 循环交换顺序 */
			while(ulBufferIndex)
			{
				ucString[ulStringIndex++] = ucBuffer[ulBufferIndex--];
			}
			
			/* 注意最后一个字符 */
			ucString[ulStringIndex++] = ucBuffer[ulBufferIndex];
		}else
		{
			/* 要发送的数据是0 */
			ucString[ulStringIndex++] = '0';
		}
		
		if(ulInNeedNewLine)
		{
			ucString[ulStringIndex++] = '\r';
			ucString[ulStringIndex++] = '\n';
		}	
		/* 指向下一个数字 */
		ulSendArray++; 
	}
	
	/* 发送字符串 */
	return vDebugSendString(ucString, ulStringIndex, 1);
}

/*
***********************************************************************
*函数名称：ErrorStatus vDebugSendLNumber(int32_t lSendNumber, uint32_t ulInNeedNewLine) 
*
*函数功能：发送数字，但是不要求必须是正数
*
*使用说明：无
*入口参数：lSendNumber：要发送的数字
					ulInNeedNewLine：是否在发送的时候进行换行操作
*返 回 值：是否操作成功
***********************************************************************
*/

ErrorStatus vDebugSendLNumber(int32_t lSendNumber, uint32_t ulInNeedNewLine) 
{
	uint8_t ucBuffer[20];
	uint8_t ucString[20];       
	uint32_t ulBufferIndex = 0, ulStringIndex = 0;
	uint32_t ulSendNumber;
	
	/* 先判断正负号 */
	if(lSendNumber > 0)
	{
		ulSendNumber = lSendNumber;
	}else
	{
		ulSendNumber = -lSendNumber;
	}
	
	/* 判断要发送的数据是不是零 */
	if(ulSendNumber)
	{
		/* 循环把数据取出来 */
		while(ulSendNumber)
		{
			/* 把最末尾的数，取出来 */
			ucBuffer[ulBufferIndex++] = (uint8_t)((ulSendNumber % 10) + '0');
			/* 移出去最后一位 */
			ulSendNumber /= 10;
		}
		
		ulBufferIndex--;
		
		/* 判断是不是需要写入负号 */
		if(lSendNumber < 0)
		{
			ucString[ulStringIndex++] = '-';
		}
			
		/* 循环交换顺序 */
		while(ulBufferIndex)
		{
			ucString[ulStringIndex++] = ucBuffer[ulBufferIndex--];
		}
		
		/* 注意最后一个字符 */
		ucString[ulStringIndex++] = ucBuffer[ulBufferIndex];
	}else
	{
		/* 要发送的数据是0 */
		ucString[ulStringIndex++] = '0';
	}
	
	if(ulInNeedNewLine)
	{
		ucString[ulStringIndex++] = '\r';
		ucString[ulStringIndex++] = '\n';
	}
	
	/* 发送字符串 */
	return vDebugSendString(ucString, ulStringIndex, 1);
}

/*
***********************************************************************
*函数名称：ErrorStatus vDebugSendLNumberWithId(int32_t lSendNumber, uint8_t ucId, uint32_t ulInNeedNewLine)  
*
*函数功能：发送数组，并且在发送的数字之前加上ID
*
*使用说明：无
*入口参数：lSendNumber：要发送的数字
					ucId：数字前面的ID
					ulInNeedNewLine：是否在发送的时候进行换行操作
*返 回 值：时候操作成功
***********************************************************************
*/

ErrorStatus vDebugSendLNumberWithId(int32_t lSendNumber, uint8_t ucId, uint32_t ulInNeedNewLine)    
{
	uint8_t ucBuffer[20];
	uint8_t ucString[20];       
	uint32_t ulBufferIndex = 0, ulStringIndex = 0;
	uint32_t ulSendNumber;
	
	/* 先判断正负号 */
	if(lSendNumber > 0)
	{
		ulSendNumber = lSendNumber;
	}else
	{
		ulSendNumber = -lSendNumber;
	}
	
	/* 判断要发送的数据是不是零 */
	if(ulSendNumber)
	{
		/* 循环把数据取出来 */
		while(ulSendNumber)
		{
			/* 把最末尾的数，取出来 */
			ucBuffer[ulBufferIndex++] = (uint8_t)((ulSendNumber % 10) + '0');
			/* 移出去最后一位 */
			ulSendNumber /= 10;
		}
		
		ulBufferIndex--;
		
		/* 在数字的前面加上ID */
		ucString[ulStringIndex++] = ucId; 
		
		/* 判断是不是需要写入负号 */
		if(lSendNumber < 0)
		{
			ucString[ulStringIndex++] = '-';
		}
			
		/* 循环交换顺序 */
		while(ulBufferIndex)
		{
			ucString[ulStringIndex++] = ucBuffer[ulBufferIndex--];
		}
		
		/* 注意最后一个字符 */
		ucString[ulStringIndex++] = ucBuffer[ulBufferIndex];
	}else
	{
		/* 要发送的数据是0 */
		ucString[ulStringIndex++] = '0';
	}
	
	if(ulInNeedNewLine)
	{
		ucString[ulStringIndex++] = '\r';
		ucString[ulStringIndex++] = '\n';
	}
	
	/* 发送字符串 */
	return vDebugSendString(ucString, ulStringIndex, 1);
}

/*
***********************************************************************
*函数名称：ErrorStatus vDebugSendLArray(int32_t * lSendArray, uint32_t ulArrayLength, uint32_t ulInNeedNewLine)  
*
*函数功能：发送数组
*
*使用说明：在函数里面不会进行数组溢出检查，需要自己保证数组不会溢出
*入口参数：lSendArray：数组指针
					ulArrayLength：数组长度
					ulInNeedNewLine：在发送的时候是否进行换行操作
*返 回 值：时候操作成功
***********************************************************************
*/

ErrorStatus vDebugSendLArray(int32_t * lSendArray, uint32_t ulArrayLength, uint32_t ulInNeedNewLine)  
{
	uint8_t ucBuffer[20];
	uint8_t ucString[200]; 
	uint32_t ulBufferIndex = 0, ulStringIndex = 0;
	uint32_t ulSendNumber;
	
	/* 循环取出来每一个数 */
	while(ulArrayLength--)
	{
		/* 先要清零缓冲区索引值,这个缓冲区是循环利用的 */
		ulBufferIndex = 0;
		/* 先判断正负号 */
		if((*lSendArray) > 0)
		{
			ulSendNumber = *lSendArray;
		}else
		{
			ulSendNumber = -(*lSendArray);
		}
		
		/* 判断要发送的数据是不是零 */
		if(ulSendNumber)
		{
			/* 循环把数据取出来 */
			while(ulSendNumber)
			{
				/* 把最末尾的数，取出来 */
				ucBuffer[ulBufferIndex++] = (uint8_t)((ulSendNumber % 10) + '0');
				/* 移出去最后一位 */
				ulSendNumber /= 10; 
			}
			
			ulBufferIndex--;
			
			/* 判断是不是需要写入负号 */
			if((*lSendArray) < 0) 
			{
				ucString[ulStringIndex++] = '-';
			}
			
			/* 循环交换顺序 */
			while(ulBufferIndex)
			{
				ucString[ulStringIndex++] = ucBuffer[ulBufferIndex--];
			}
			
			/* 注意最后一个字符 */
			ucString[ulStringIndex++] = ucBuffer[ulBufferIndex];
		}else
		{
			/* 要发送的数据是0 */
			ucString[ulStringIndex++] = '0';
		}
		
		if(ulInNeedNewLine)
		{
			ucString[ulStringIndex++] = '\r';
			ucString[ulStringIndex++] = '\n';
		}	
		
		/* 指向下一个数字 */
		lSendArray++; 
	}
	
	/* 发送字符串 */
	return vDebugSendString(ucString, ulStringIndex, 1);
}

/*
***********************************************************************
*函数名称：ErrorStatus vDebugSendLArrayWithId(int32_t * lSendArray, uint8_t * pucId, uint32_t ulArrayLength, uint32_t ulInNeedNewLine)  
*
*函数功能：发送数组，并且在发送的数字之前加上ID
*
*使用说明：在函数里面不会进行数组溢出检查，需要自己保证数组不会溢出
*入口参数：lSendArray：发送数组的指针
					pucId：数字前面的ID的指针
					ulArrayLength：要发送的数组的长度
					ulInNeedNewLine：在发送的时候，是否要进行换行操作
*返 回 值：时候操作成功
***********************************************************************
*/

ErrorStatus vDebugSendLArrayWithId(int32_t * lSendArray, uint8_t * pucId, uint32_t ulArrayLength, uint32_t ulInNeedNewLine)  
{
	uint8_t ucBuffer[20];
	uint8_t ucString[200]; 
	uint32_t ulBufferIndex = 0, ulStringIndex = 0;
	uint32_t ulSendNumber;
	
	/* 循环取出来每一个数 */
	while(ulArrayLength--)
	{
		/* 先要清零缓冲区索引值,这个缓冲区是循环利用的 */
		ulBufferIndex = 0;
		/* 先判断正负号 */
		if((*lSendArray) > 0)
		{
			ulSendNumber = *lSendArray;
		}else
		{
			ulSendNumber = -(*lSendArray);
		}
		
		/* 判断要发送的数据是不是零 */
		if(ulSendNumber)
		{
			/* 循环把数据取出来 */
			while(ulSendNumber)
			{
				/* 把最末尾的数，取出来 */
				ucBuffer[ulBufferIndex++] = (uint8_t)((ulSendNumber % 10) + '0');
				/* 移出去最后一位 */
				ulSendNumber /= 10; 
			}
			
			ulBufferIndex--;
			
			/* 在前面加上数字的ID */
			ucString[ulStringIndex++] = *pucId++;
			
			/* 判断是不是需要写入负号 */
			if((*lSendArray) < 0) 
			{
				ucString[ulStringIndex++] = '-';
			}
			
			/* 循环交换顺序 */
			while(ulBufferIndex)
			{
				ucString[ulStringIndex++] = ucBuffer[ulBufferIndex--];
			}
			
			/* 注意最后一个字符 */
			ucString[ulStringIndex++] = ucBuffer[ulBufferIndex];
		}else
		{
			/* 要发送的数据是0 */
			ucString[ulStringIndex++] = '0';
		}
		
		if(ulInNeedNewLine)
		{
			ucString[ulStringIndex++] = '\r';
			ucString[ulStringIndex++] = '\n';
		}	
		
		/* 指向下一个数字 */
		lSendArray++; 
	}
	
	/* 发送字符串 */
	return vDebugSendString(ucString, ulStringIndex, 1);
}

/*
***********************************************************************
*函数名称：ErrorStatus vDebugSendFNumber(float fSendNumber, uint32_t ulInNeedNewLine) 
*
*函数功能：发送float类型的数字
*
*使用说明：无
*入口参数：fSendNumber：要发送的数字
					ulInNeedNewLine：时候进行换行操作
*返 回 值：时候操作成功
***********************************************************************
*/

ErrorStatus vDebugSendFNumber(float fSendNumber, uint32_t ulInNeedNewLine) 
{
	return vDebugSendLNumber((int32_t)(fSendNumber*100.0f), ulInNeedNewLine);
}

/*
***********************************************************************
*函数名称：ErrorStatus vDebugSendFNumberWithId(float fSendNumber, uint8_t ucId, uint32_t ulInNeedNewLine) 
*
*函数功能：发送float数字，并且在数字的前面加上ID
*
*使用说明：无
*入口参数：fSendNumber：要发送的数字
					ucId：数字前面的ID
					ulInNeedNewLine：时候进行换行操作
*返 回 值：时候操作成功
***********************************************************************
*/

ErrorStatus vDebugSendFNumberWithId(float fSendNumber, uint8_t ucId, uint32_t ulInNeedNewLine) 
{
	return vDebugSendLNumberWithId((int32_t)(fSendNumber*100.0f), ucId, ulInNeedNewLine);  
}

/*
***********************************************************************
*函数名称：ErrorStatus vDebugSendFArray(float * fSendArray, uint32_t ulArrayLength, uint32_t ulInNeedNewLine)
*
*函数功能：发送float类型的数组
*
*使用说明：无
*入口参数：fSendArray：数组指针
					ulArrayLength：数组的长度
					ulInNeedNewLine：是否进行换行操作
*返 回 值：是否操作成功
***********************************************************************
*/

ErrorStatus vDebugSendFArray(float * fSendArray, uint32_t ulArrayLength, uint32_t ulInNeedNewLine) 
{
	int32_t ulNumberArray[10];
	uint32_t ulArrayLengthBackup = ulArrayLength;
	
	do
	{
		ulArrayLengthBackup--;
		ulNumberArray[ulArrayLengthBackup] = (int32_t)(fSendArray[ulArrayLengthBackup]*100.0f); 
	}while(ulArrayLengthBackup);
	
	return vDebugSendLArray(ulNumberArray, ulArrayLength, ulInNeedNewLine);
}

/*
***********************************************************************
*函数名称：ErrorStatus vDebugSendFArrayWithId(float * fSendArray, uint8_t * pucId, uint32_t ulArrayLength, uint32_t ulInNeedNewLine) 
*
*函数功能：发送float类型的数组，并且在数字前面加上ID
*
*使用说明：无
*入口参数：fSendArray：数组指针
					pucId：ID指针
					ulArrayLength：要发送的数组长度
					ulInNeedNewLine：时候进行换行操作
*返 回 值：是否操作成功
***********************************************************************
*/

ErrorStatus vDebugSendFArrayWithId(float * fSendArray, uint8_t * pucId, uint32_t ulArrayLength, uint32_t ulInNeedNewLine) 
{
	int32_t ulNumberArray[10];
	uint32_t ulArrayLengthBackup = ulArrayLength;
	
	do
	{
		ulArrayLengthBackup--;
		ulNumberArray[ulArrayLengthBackup] = (int32_t)(fSendArray[ulArrayLengthBackup]*100.0f); 
	}while(ulArrayLengthBackup);
	
	return vDebugSendLArrayWithId(ulNumberArray, pucId, ulArrayLength, ulInNeedNewLine);
}

/* end of file cppyright reserve by team of yanjun ,More information please browse www.yanjuntech.cn */
