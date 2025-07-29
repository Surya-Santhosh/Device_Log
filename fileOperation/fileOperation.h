//****************************** fileoperation *********************************
// Copyright (c) 2025 Trenser Technology Solutions
// All Rights Reserved 
//******************************************************************************
//
// Summary : Wraper function for file operation such as fopen, fclose, fread, 
//           fwrite, fseek.
// Note    : None
// 
//******************************************************************************
#ifndef FILEOPERATION_H
#define FILEOPERATION_H

//**************************** Include Files ***********************************
#include "commonHeader.h"

//*************************** Global Types ************************************* 

//************************* Global Constants *********************************** 

//************************* Global Variables *********************************** 

//************************* Forward Declarations ******************************* 
bool fileOperationOpen(FILE **pstFile, const char *pcFileName, 
                       const char *pcMode);
bool fileOperationClose(FILE **ppstFile);
bool fileOperationAppendandWrite(FILE **ppstFile, const char *pcFileName);
bool fileOperationFread(void *stDeviceInfo, uint8 cSize, FILE **ppstFile);
bool fileOperationWrite(uint8 cSize, FILE *pstFile, void *pstcurrent);
bool fileOperationReadwithFseek(FILE **ppstFile, const char *pcFileName);
bool fileOperationFseek(FILE **ppstFile, uint8 cOffset, uint8 cPosition);
                        
//********************** Inline Method Implementations ************************* 

#endif 

// FILEOPERATION_H 
// EOF