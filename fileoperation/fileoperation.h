//******************************* DeviceLog ************************************
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
#include "devicelog.h"

//******************************* Global Types ********************************* 


//***************************** Global Constants ******************************* 

//***************************** Global Variables ******************************* 

//**************************** Forward Declarations **************************** 
bool fileoperationOpen(FILE **pstFile, int8 *cFileName, int8 *cMode);
bool fileoperationClose(FILE **ppstFile);
bool fileoperationCheck(FILE **ppstFile, int8 *cFileName, int8 *cMode, 
                            NODE **ppstHead);
bool fileoperationFread(DEVICE_INFO *stDeviceInfo, FILE **ppstFile);
bool fileoperationWrite(NODE **pstcurrent, FILE **ppstFile);

//*********************** Inline Method Implementations ************************ 

#endif 
// _DEVICELOG_H_ 
// EOF 
