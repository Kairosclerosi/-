#ifndef _UTIL_H
#define _UTIL_H

#include "system.h"

ErrorStatus vCompareString(uint8_t * pucSrc, uint8_t * pucDes, uint32_t ulLength);

ErrorStatus vDebugSendString(uint8_t * pucBuffer, uint32_t ulSize, uint32_t ulIsNeedCopyData);

ErrorStatus vDebugSendUlNumber(uint32_t ulSendNumber, uint32_t ulInNeedNewLine);
ErrorStatus vDebugSendUlNumberWithId(uint32_t ulSendNumber, uint8_t ucId, uint32_t ulInNeedNewLine);
ErrorStatus vDebugSendUlArray(uint32_t * ulSendArray, uint32_t ulArrayLength, uint32_t ulInNeedNewLine);
ErrorStatus vDebugSendUlArrayWithId(uint32_t * ulSendArray, uint8_t * pucId, uint32_t ulArrayLength, uint32_t ulInNeedNewLine);

ErrorStatus vDebugSendLNumber(int32_t lSendNumber, uint32_t ulInNeedNewLine);
ErrorStatus vDebugSendLNumberWithId(int32_t lSendNumber, uint8_t ucId, uint32_t ulInNeedNewLine);
ErrorStatus vDebugSendLArray(int32_t * lSendArray, uint32_t ulArrayLength, uint32_t ulInNeedNewLine);
ErrorStatus vDebugSendLArrayWithId(int32_t * lSendArray, uint8_t * pucId, uint32_t ulArrayLength, uint32_t ulInNeedNewLine);

ErrorStatus vDebugSendFNumber(float fSendNumber, uint32_t ulInNeedNewLine);
ErrorStatus vDebugSendFNumberWithId(float fSendNumber, uint8_t ucId, uint32_t ulInNeedNewLine);
ErrorStatus vDebugSendFArray(float * fSendArray, uint32_t ulArrayLength, uint32_t ulInNeedNewLine);
ErrorStatus vDebugSendFArrayWithId(float * fSendArray, uint8_t * pucId, uint32_t ulArrayLength, uint32_t ulInNeedNewLine);

#endif

/* end of file cppyright reserve by team of yanjun ,More information please browse www.yanjuntech.cn */
