#include "util.h"
#include "usart1_dma.h"

/*
***********************************************************************
*�������ƣ�ErrorStatus vCompareString(uint8_t * src, uint8_t * des, uint32_t length)
*
*�������ܣ��Ƚ������ַ����Ƿ���ͬ
*
*ʹ��˵������
*��ڲ�����pucSrc:�ַ���1
					pucDes���ַ���2
					ulLength��Ҫ�Ƚϵĳ���
*�� �� ֵ����
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
*�������ƣ�ErrorStatus vDebugSendString(uint8_t * pucBuffer, uint32_t ulSize, uint32_t ulIsNeedCopyData) 
*
*�������ܣ������ַ������������ǶԵײ�ķ�װ
*
*ʹ��˵������
*��ڲ�����pucBuffer:Ҫ���͵��ַ���ָ��
					ulSize��Ҫ�����ַ����ĳ���
					ulIsNeedCopyData���Ƿ���Ҫ�����ַ������ڴ滺������
*�� �� ֵ���Ƿ���ô���
***********************************************************************
*/

ErrorStatus vDebugSendString(uint8_t * pucBuffer, uint32_t ulSize, uint32_t ulIsNeedCopyData) 
{
	return vUSART1_DmaTxStart(pucBuffer, ulSize, ulIsNeedCopyData); 
}

/*
***********************************************************************
*�������ƣ�ErrorStatus vDebugSendUlNumber(uint32_t ulSendNumber, uint32_t ulInNeedNewLine) 
*
*�������ܣ������޷��ŵ�32λ����
*
*ʹ��˵���������������������
*��ڲ�����ulSendNumber��Ҫ���͵�����
					ulInNeedNewLine���Ƿ���Ҫ����
*�� �� ֵ���Ƿ�����ɹ�
***********************************************************************
*/

ErrorStatus vDebugSendUlNumber(uint32_t ulSendNumber, uint32_t ulInNeedNewLine) 
{
	uint8_t ucBuffer[20];
	uint8_t ucString[20];       
	uint32_t ulBufferIndex = 0, ulStringIndex = 0;
	
	/* �ж�Ҫ���͵������ǲ����� */
	if(ulSendNumber)
	{
		/* ѭ��������ȡ���� */
		while(ulSendNumber)
		{
			/* ����ĩβ������ȡ���� */
			ucBuffer[ulBufferIndex++] = (uint8_t)((ulSendNumber % 10) + '0');
			/* �Ƴ�ȥ���һλ */
			ulSendNumber /= 10;
		}
		
		ulBufferIndex--;
		
		/* ѭ������˳�� */
		while(ulBufferIndex)
		{
			ucString[ulStringIndex++] = ucBuffer[ulBufferIndex--];
		}
		
		/* ע�����һ���ַ� */
		ucString[ulStringIndex++] = ucBuffer[ulBufferIndex];
	}else
	{
		/* Ҫ���͵�������0 */
		ucString[ulStringIndex++] = '0';
	}
	
	if(ulInNeedNewLine)
	{
		ucString[ulStringIndex++] = '\r';
		ucString[ulStringIndex++] = '\n';
	}
	
	/* �����ַ��� */
	return vDebugSendString(ucString, ulStringIndex, 1);
}

/*
***********************************************************************
*�������ƣ�ErrorStatus vDebugSendUlNumberWithId(uint32_t ulSendNumber, uint8_t ucId, uint32_t ulInNeedNewLine) 
*
*�������ܣ������������֣�����������ǰ�����һ��ID
*
*ʹ��˵�������ֱ���������
*��ڲ�����ulSendNumber��Ҫ���͵�����
					ucId������ǰ���ID
					ulInNeedNewLine���Ƿ���Ҫ����
*�� �� ֵ���Ƿ�����ɹ�
***********************************************************************
*/

ErrorStatus vDebugSendUlNumberWithId(uint32_t ulSendNumber, uint8_t ucId, uint32_t ulInNeedNewLine) 
{
	uint8_t ucBuffer[20];
	uint8_t ucString[20];       
	uint32_t ulBufferIndex = 0, ulStringIndex = 0;
	
	/* �ж�Ҫ���͵������ǲ����� */
	if(ulSendNumber)
	{
		/* ѭ��������ȡ���� */
		while(ulSendNumber)
		{
			/* ����ĩβ������ȡ���� */
			ucBuffer[ulBufferIndex++] = (uint8_t)((ulSendNumber % 10) + '0');
			/* �Ƴ�ȥ���һλ */
			ulSendNumber /= 10;
		}
		
		ulBufferIndex--;
		
		/* �ڿ�ͷ�������ֵ�ID */
		ucString[ulStringIndex++] = ucId;   
		
		/* ѭ������˳�� */
		while(ulBufferIndex)
		{
			ucString[ulStringIndex++] = ucBuffer[ulBufferIndex--];
		}
		
		/* ע�����һ���ַ� */
		ucString[ulStringIndex++] = ucBuffer[ulBufferIndex];
	}else
	{
		/* Ҫ���͵�������0 */
		ucString[ulStringIndex++] = '0';
	}
	
	if(ulInNeedNewLine)
	{
		ucString[ulStringIndex++] = '\r';
		ucString[ulStringIndex++] = '\n';
	}
	
	/* �����ַ��� */
	return vDebugSendString(ucString, ulStringIndex, 1);
}

/*
***********************************************************************
*�������ƣ�ErrorStatus vDebugSendUlArray(uint32_t * ulSendArray, uint32_t ulArrayLength, uint32_t ulInNeedNewLine) 
*
*�������ܣ�������������
*
*ʹ��˵�������͵Ķ�������
*��ڲ�����ulSendArray������ָ��
					ulArrayLength��Ҫ��������ĳ���
					ulInNeedNewLine���Ƿ��ڷ��͵�ʱ����л���
*�� �� ֵ���Ƿ�����ɹ�
***********************************************************************
*/

ErrorStatus vDebugSendUlArray(uint32_t * ulSendArray, uint32_t ulArrayLength, uint32_t ulInNeedNewLine) 
{
	uint8_t ucBuffer[20];
	uint8_t ucString[200]; 
	uint32_t ulBufferIndex = 0, ulStringIndex = 0;
	
	/* ѭ��ȡ����ÿһ���� */
	while(ulArrayLength--)
	{
		/* ��Ҫ���㻺��������ֵ,�����������ѭ�����õ� */
		ulBufferIndex = 0;
		/* �ж�Ҫ���͵������ǲ����� */
		if(*ulSendArray)
		{
			/* ѭ��������ȡ���� */
			while(*ulSendArray)
			{
				/* ����ĩβ������ȡ���� */
				ucBuffer[ulBufferIndex++] = (uint8_t)(((*ulSendArray) % 10) + '0');
				/* �Ƴ�ȥ���һλ */
				(*ulSendArray) /= 10; 
			}
			
			ulBufferIndex--;
			
			/* ѭ������˳�� */
			while(ulBufferIndex)
			{
				ucString[ulStringIndex++] = ucBuffer[ulBufferIndex--];
			}
			
			/* ע�����һ���ַ� */
			ucString[ulStringIndex++] = ucBuffer[ulBufferIndex];
		}else
		{
			/* Ҫ���͵�������0 */
			ucString[ulStringIndex++] = '0';
		}
		
		if(ulInNeedNewLine)
		{
			ucString[ulStringIndex++] = '\r';
			ucString[ulStringIndex++] = '\n';
		}	
		/* ָ����һ������ */
		ulSendArray++; 
	}
	
	/* �����ַ��� */
	return vDebugSendString(ucString, ulStringIndex, 1);
}

/*
***********************************************************************
*�������ƣ�ErrorStatus vDebugSendUlArrayWithId(uint32_t * ulSendArray, uint8_t * pucId, uint32_t ulArrayLength, uint32_t ulInNeedNewLine) 
*
*�������ܣ������������飬������ÿ������ǰ�����ID
*
*ʹ��˵�������͵Ķ�������
					�ں������治���������Խ���飬������Ҫ�Լ���֤���鲻��Խ��
*��ڲ�����ulSendArray�����͵�����ָ��
					pucId��ÿ������ǰ���ID
					ulArrayLength��Ҫ���͵����鳤��
					ulInNeedNewLine��ʱ���ٷ��͵�ʱ����л���
*�� �� ֵ���Ƿ�����ɹ�
***********************************************************************
*/

ErrorStatus vDebugSendUlArrayWithId(uint32_t * ulSendArray, uint8_t * pucId, uint32_t ulArrayLength, uint32_t ulInNeedNewLine) 
{
	uint8_t ucBuffer[20];
	uint8_t ucString[200]; 
	uint32_t ulBufferIndex = 0, ulStringIndex = 0;
	
	/* ѭ��ȡ����ÿһ���� */
	while(ulArrayLength--)
	{
		/* ��Ҫ���㻺��������ֵ,�����������ѭ�����õ� */
		ulBufferIndex = 0;
		/* �ж�Ҫ���͵������ǲ����� */
		if(*ulSendArray)
		{
			/* ѭ��������ȡ���� */
			while(*ulSendArray)
			{
				/* ����ĩβ������ȡ���� */
				ucBuffer[ulBufferIndex++] = (uint8_t)(((*ulSendArray) % 10) + '0');
				/* �Ƴ�ȥ���һλ */
				(*ulSendArray) /= 10; 
			}
			
			ulBufferIndex--;
			
			/* �ڿ�ͷ�������ֵ�ID */
			ucString[ulStringIndex++] = *pucId++;
			
			/* ѭ������˳�� */
			while(ulBufferIndex)
			{
				ucString[ulStringIndex++] = ucBuffer[ulBufferIndex--];
			}
			
			/* ע�����һ���ַ� */
			ucString[ulStringIndex++] = ucBuffer[ulBufferIndex];
		}else
		{
			/* Ҫ���͵�������0 */
			ucString[ulStringIndex++] = '0';
		}
		
		if(ulInNeedNewLine)
		{
			ucString[ulStringIndex++] = '\r';
			ucString[ulStringIndex++] = '\n';
		}	
		/* ָ����һ������ */
		ulSendArray++; 
	}
	
	/* �����ַ��� */
	return vDebugSendString(ucString, ulStringIndex, 1);
}

/*
***********************************************************************
*�������ƣ�ErrorStatus vDebugSendLNumber(int32_t lSendNumber, uint32_t ulInNeedNewLine) 
*
*�������ܣ��������֣����ǲ�Ҫ�����������
*
*ʹ��˵������
*��ڲ�����lSendNumber��Ҫ���͵�����
					ulInNeedNewLine���Ƿ��ڷ��͵�ʱ����л��в���
*�� �� ֵ���Ƿ�����ɹ�
***********************************************************************
*/

ErrorStatus vDebugSendLNumber(int32_t lSendNumber, uint32_t ulInNeedNewLine) 
{
	uint8_t ucBuffer[20];
	uint8_t ucString[20];       
	uint32_t ulBufferIndex = 0, ulStringIndex = 0;
	uint32_t ulSendNumber;
	
	/* ���ж������� */
	if(lSendNumber > 0)
	{
		ulSendNumber = lSendNumber;
	}else
	{
		ulSendNumber = -lSendNumber;
	}
	
	/* �ж�Ҫ���͵������ǲ����� */
	if(ulSendNumber)
	{
		/* ѭ��������ȡ���� */
		while(ulSendNumber)
		{
			/* ����ĩβ������ȡ���� */
			ucBuffer[ulBufferIndex++] = (uint8_t)((ulSendNumber % 10) + '0');
			/* �Ƴ�ȥ���һλ */
			ulSendNumber /= 10;
		}
		
		ulBufferIndex--;
		
		/* �ж��ǲ�����Ҫд�븺�� */
		if(lSendNumber < 0)
		{
			ucString[ulStringIndex++] = '-';
		}
			
		/* ѭ������˳�� */
		while(ulBufferIndex)
		{
			ucString[ulStringIndex++] = ucBuffer[ulBufferIndex--];
		}
		
		/* ע�����һ���ַ� */
		ucString[ulStringIndex++] = ucBuffer[ulBufferIndex];
	}else
	{
		/* Ҫ���͵�������0 */
		ucString[ulStringIndex++] = '0';
	}
	
	if(ulInNeedNewLine)
	{
		ucString[ulStringIndex++] = '\r';
		ucString[ulStringIndex++] = '\n';
	}
	
	/* �����ַ��� */
	return vDebugSendString(ucString, ulStringIndex, 1);
}

/*
***********************************************************************
*�������ƣ�ErrorStatus vDebugSendLNumberWithId(int32_t lSendNumber, uint8_t ucId, uint32_t ulInNeedNewLine)  
*
*�������ܣ��������飬�����ڷ��͵�����֮ǰ����ID
*
*ʹ��˵������
*��ڲ�����lSendNumber��Ҫ���͵�����
					ucId������ǰ���ID
					ulInNeedNewLine���Ƿ��ڷ��͵�ʱ����л��в���
*�� �� ֵ��ʱ������ɹ�
***********************************************************************
*/

ErrorStatus vDebugSendLNumberWithId(int32_t lSendNumber, uint8_t ucId, uint32_t ulInNeedNewLine)    
{
	uint8_t ucBuffer[20];
	uint8_t ucString[20];       
	uint32_t ulBufferIndex = 0, ulStringIndex = 0;
	uint32_t ulSendNumber;
	
	/* ���ж������� */
	if(lSendNumber > 0)
	{
		ulSendNumber = lSendNumber;
	}else
	{
		ulSendNumber = -lSendNumber;
	}
	
	/* �ж�Ҫ���͵������ǲ����� */
	if(ulSendNumber)
	{
		/* ѭ��������ȡ���� */
		while(ulSendNumber)
		{
			/* ����ĩβ������ȡ���� */
			ucBuffer[ulBufferIndex++] = (uint8_t)((ulSendNumber % 10) + '0');
			/* �Ƴ�ȥ���һλ */
			ulSendNumber /= 10;
		}
		
		ulBufferIndex--;
		
		/* �����ֵ�ǰ�����ID */
		ucString[ulStringIndex++] = ucId; 
		
		/* �ж��ǲ�����Ҫд�븺�� */
		if(lSendNumber < 0)
		{
			ucString[ulStringIndex++] = '-';
		}
			
		/* ѭ������˳�� */
		while(ulBufferIndex)
		{
			ucString[ulStringIndex++] = ucBuffer[ulBufferIndex--];
		}
		
		/* ע�����һ���ַ� */
		ucString[ulStringIndex++] = ucBuffer[ulBufferIndex];
	}else
	{
		/* Ҫ���͵�������0 */
		ucString[ulStringIndex++] = '0';
	}
	
	if(ulInNeedNewLine)
	{
		ucString[ulStringIndex++] = '\r';
		ucString[ulStringIndex++] = '\n';
	}
	
	/* �����ַ��� */
	return vDebugSendString(ucString, ulStringIndex, 1);
}

/*
***********************************************************************
*�������ƣ�ErrorStatus vDebugSendLArray(int32_t * lSendArray, uint32_t ulArrayLength, uint32_t ulInNeedNewLine)  
*
*�������ܣ���������
*
*ʹ��˵�����ں������治��������������飬��Ҫ�Լ���֤���鲻�����
*��ڲ�����lSendArray������ָ��
					ulArrayLength�����鳤��
					ulInNeedNewLine���ڷ��͵�ʱ���Ƿ���л��в���
*�� �� ֵ��ʱ������ɹ�
***********************************************************************
*/

ErrorStatus vDebugSendLArray(int32_t * lSendArray, uint32_t ulArrayLength, uint32_t ulInNeedNewLine)  
{
	uint8_t ucBuffer[20];
	uint8_t ucString[200]; 
	uint32_t ulBufferIndex = 0, ulStringIndex = 0;
	uint32_t ulSendNumber;
	
	/* ѭ��ȡ����ÿһ���� */
	while(ulArrayLength--)
	{
		/* ��Ҫ���㻺��������ֵ,�����������ѭ�����õ� */
		ulBufferIndex = 0;
		/* ���ж������� */
		if((*lSendArray) > 0)
		{
			ulSendNumber = *lSendArray;
		}else
		{
			ulSendNumber = -(*lSendArray);
		}
		
		/* �ж�Ҫ���͵������ǲ����� */
		if(ulSendNumber)
		{
			/* ѭ��������ȡ���� */
			while(ulSendNumber)
			{
				/* ����ĩβ������ȡ���� */
				ucBuffer[ulBufferIndex++] = (uint8_t)((ulSendNumber % 10) + '0');
				/* �Ƴ�ȥ���һλ */
				ulSendNumber /= 10; 
			}
			
			ulBufferIndex--;
			
			/* �ж��ǲ�����Ҫд�븺�� */
			if((*lSendArray) < 0) 
			{
				ucString[ulStringIndex++] = '-';
			}
			
			/* ѭ������˳�� */
			while(ulBufferIndex)
			{
				ucString[ulStringIndex++] = ucBuffer[ulBufferIndex--];
			}
			
			/* ע�����һ���ַ� */
			ucString[ulStringIndex++] = ucBuffer[ulBufferIndex];
		}else
		{
			/* Ҫ���͵�������0 */
			ucString[ulStringIndex++] = '0';
		}
		
		if(ulInNeedNewLine)
		{
			ucString[ulStringIndex++] = '\r';
			ucString[ulStringIndex++] = '\n';
		}	
		
		/* ָ����һ������ */
		lSendArray++; 
	}
	
	/* �����ַ��� */
	return vDebugSendString(ucString, ulStringIndex, 1);
}

/*
***********************************************************************
*�������ƣ�ErrorStatus vDebugSendLArrayWithId(int32_t * lSendArray, uint8_t * pucId, uint32_t ulArrayLength, uint32_t ulInNeedNewLine)  
*
*�������ܣ��������飬�����ڷ��͵�����֮ǰ����ID
*
*ʹ��˵�����ں������治��������������飬��Ҫ�Լ���֤���鲻�����
*��ڲ�����lSendArray�����������ָ��
					pucId������ǰ���ID��ָ��
					ulArrayLength��Ҫ���͵�����ĳ���
					ulInNeedNewLine���ڷ��͵�ʱ���Ƿ�Ҫ���л��в���
*�� �� ֵ��ʱ������ɹ�
***********************************************************************
*/

ErrorStatus vDebugSendLArrayWithId(int32_t * lSendArray, uint8_t * pucId, uint32_t ulArrayLength, uint32_t ulInNeedNewLine)  
{
	uint8_t ucBuffer[20];
	uint8_t ucString[200]; 
	uint32_t ulBufferIndex = 0, ulStringIndex = 0;
	uint32_t ulSendNumber;
	
	/* ѭ��ȡ����ÿһ���� */
	while(ulArrayLength--)
	{
		/* ��Ҫ���㻺��������ֵ,�����������ѭ�����õ� */
		ulBufferIndex = 0;
		/* ���ж������� */
		if((*lSendArray) > 0)
		{
			ulSendNumber = *lSendArray;
		}else
		{
			ulSendNumber = -(*lSendArray);
		}
		
		/* �ж�Ҫ���͵������ǲ����� */
		if(ulSendNumber)
		{
			/* ѭ��������ȡ���� */
			while(ulSendNumber)
			{
				/* ����ĩβ������ȡ���� */
				ucBuffer[ulBufferIndex++] = (uint8_t)((ulSendNumber % 10) + '0');
				/* �Ƴ�ȥ���һλ */
				ulSendNumber /= 10; 
			}
			
			ulBufferIndex--;
			
			/* ��ǰ��������ֵ�ID */
			ucString[ulStringIndex++] = *pucId++;
			
			/* �ж��ǲ�����Ҫд�븺�� */
			if((*lSendArray) < 0) 
			{
				ucString[ulStringIndex++] = '-';
			}
			
			/* ѭ������˳�� */
			while(ulBufferIndex)
			{
				ucString[ulStringIndex++] = ucBuffer[ulBufferIndex--];
			}
			
			/* ע�����һ���ַ� */
			ucString[ulStringIndex++] = ucBuffer[ulBufferIndex];
		}else
		{
			/* Ҫ���͵�������0 */
			ucString[ulStringIndex++] = '0';
		}
		
		if(ulInNeedNewLine)
		{
			ucString[ulStringIndex++] = '\r';
			ucString[ulStringIndex++] = '\n';
		}	
		
		/* ָ����һ������ */
		lSendArray++; 
	}
	
	/* �����ַ��� */
	return vDebugSendString(ucString, ulStringIndex, 1);
}

/*
***********************************************************************
*�������ƣ�ErrorStatus vDebugSendFNumber(float fSendNumber, uint32_t ulInNeedNewLine) 
*
*�������ܣ�����float���͵�����
*
*ʹ��˵������
*��ڲ�����fSendNumber��Ҫ���͵�����
					ulInNeedNewLine��ʱ����л��в���
*�� �� ֵ��ʱ������ɹ�
***********************************************************************
*/

ErrorStatus vDebugSendFNumber(float fSendNumber, uint32_t ulInNeedNewLine) 
{
	return vDebugSendLNumber((int32_t)(fSendNumber*100.0f), ulInNeedNewLine);
}

/*
***********************************************************************
*�������ƣ�ErrorStatus vDebugSendFNumberWithId(float fSendNumber, uint8_t ucId, uint32_t ulInNeedNewLine) 
*
*�������ܣ�����float���֣����������ֵ�ǰ�����ID
*
*ʹ��˵������
*��ڲ�����fSendNumber��Ҫ���͵�����
					ucId������ǰ���ID
					ulInNeedNewLine��ʱ����л��в���
*�� �� ֵ��ʱ������ɹ�
***********************************************************************
*/

ErrorStatus vDebugSendFNumberWithId(float fSendNumber, uint8_t ucId, uint32_t ulInNeedNewLine) 
{
	return vDebugSendLNumberWithId((int32_t)(fSendNumber*100.0f), ucId, ulInNeedNewLine);  
}

/*
***********************************************************************
*�������ƣ�ErrorStatus vDebugSendFArray(float * fSendArray, uint32_t ulArrayLength, uint32_t ulInNeedNewLine)
*
*�������ܣ�����float���͵�����
*
*ʹ��˵������
*��ڲ�����fSendArray������ָ��
					ulArrayLength������ĳ���
					ulInNeedNewLine���Ƿ���л��в���
*�� �� ֵ���Ƿ�����ɹ�
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
*�������ƣ�ErrorStatus vDebugSendFArrayWithId(float * fSendArray, uint8_t * pucId, uint32_t ulArrayLength, uint32_t ulInNeedNewLine) 
*
*�������ܣ�����float���͵����飬����������ǰ�����ID
*
*ʹ��˵������
*��ڲ�����fSendArray������ָ��
					pucId��IDָ��
					ulArrayLength��Ҫ���͵����鳤��
					ulInNeedNewLine��ʱ����л��в���
*�� �� ֵ���Ƿ�����ɹ�
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
