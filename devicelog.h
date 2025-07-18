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
#ifndef _DEVICELOG_H_
#define _DEVICELOG_H_

//******************************* Include Files ********************************
#include "common.h"

//******************************* Global Types ********************************* 
typedef struct DEVICE_INFO
{
    uint16 unUID;
    uint16 unDeviceID;
    uint16 unVentorID;
    uint8 ucName[MAX_CHAR_SIZE];
    //char is used for string operations.
    char ucState[MAX_CHAR_SIZE];
}DEVICE_INFO;

typedef struct NODE
{
    DEVICE_INFO stDeviceInfo;
    struct NODE* pstNext;
}NODE;

typedef bool (*Function)(NODE **, FILE **);

//***************************** Global Constants ******************************* 

//***************************** Global Variables ******************************* 

//**************************** Forward Declarations **************************** 
bool devicelogReadFromFile(NODE **ppstHead, FILE **pstFile);
bool devicelogPrintAllDevices(FILE **pstFile);
bool devicelogAddNewtotheList(NODE **ppstHead, FILE **pstFile);
bool devicelogSearchFromList(NODE **ppstHead, FILE **pstFile);
bool devicelogDeleteFromList(NODE **ppstHead, FILE **pstFile);
bool devicelogFreeList (NODE **ppstHead);

//*********************** Inline Method Implementations ************************ 

#endif 
// _DEVICELOG_H_ 
// EOF 
