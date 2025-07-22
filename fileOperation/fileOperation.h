//***************************** fileoperation **********************************
// Copyright (c) 2025 Trenser Technology Solutions
// All Rights Reserved 
//****************************************************************************** 
//
// Summary : Store and update device information using a linked list and a 
//           binary file.
// Note    : None
// 
//****************************************************************************** 
#ifndef _FILEOPERATION_H_
#define _FILEOPERATION_H_

//******************************* Include Files ********************************
#include "common.h"

//******************************* Global Types ********************************* 


//***************************** Global Constants ******************************* 

//***************************** Global Variables ******************************* 

//**************************** Forward Declarations **************************** 
bool fileOperationOpen(FILE **pstFile, int8 *cFileName, int8 *cMode);
bool fileOperationClose(FILE **ppstFile);
bool fileOperationOpenwithFseek(FILE **ppstFile, int8 *cFileName, int8 *cMode);
bool fileOperationFread(int8 *stDeviceInfo, int8 cSize, int8 cCount, 
                        FILE *pstFile);
bool fileOperationWrite(int8 cSize, int8 cCount, FILE *pstFile, 
                        int8 *pstcurrent);

//*********************** Inline Method Implementations ************************ 

#endif 
// _FILEOPERATION_H_ 
// EOF 

