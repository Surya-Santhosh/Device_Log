//***************************** DeviceLog **************************************
// Copyright (c) 2025 Trenser Technology Solutions
// All Rights Reserved 
//******************************************************************************
//
// Summary : Store and update device information using a linked list and a 
//           binary file.
// Note    : None
// 
//******************************************************************************
#ifndef DEVICELOG_H
#define DEVICELOG_H

//**************************** Include Files ***********************************
#include "commonHeader.h"
#include "memmoryHandle.h"
#include "fileOperation.h"

//*************************** Global Types ************************************* 

//************************* Global Constants *********************************** 

//************************* Global Variables *********************************** 

//************************* Forward Declarations ******************************* 
bool devicelogManager(NODE **ppstHead, FILE **ppstFile);

//********************** Inline Method Implementations *************************

#endif 

// DEVICELOG_H 
// EOF