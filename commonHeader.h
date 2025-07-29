//***************************** commonHeader ***********************************
// Copyright (c) 2025 Trenser Technology Solutions
// All Rights Reserved 
//****************************************************************************** 
// 
// Summary : Typedefs are included.
// Note    : None
// 
//******************************************************************************
#ifndef COMMONHEADER_H
#define COMMONHEADER_H

//**************************** Include Files *********************************** 
#include "common.h"

//**************************** Global Types ************************************
typedef struct DEVICE_INFO
{
    uint16 unUID;
    uint8 unDeviceID;
    uint8 unVendorID;
    int8 ucName[MAX_CHAR_SIZE];
    int8 ucState[MAX_CHAR_SIZE];
}DEVICE_INFO;

typedef struct NODE
{
    DEVICE_INFO stDeviceInfo;
    struct NODE* pstNext;
}NODE;

typedef struct DEVICE_MANAGEMENT
{
    int8 cMenu[MAX_CHAR_SIZE];
    bool (*pFunction)(NODE **, FILE **);
}DEVICE_MANAGEMENT;

//************************* Global Constants *********************************** 

//************************* Global Variables *********************************** 

//************************* Forward Declarations *******************************  

//************************ Inline Method Implementations *********************** 

#endif 

// COMMONHEADER_H 
// EOF
