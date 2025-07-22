//****************************** fileoperation *********************************
// Copyright (c) 2025 Trenser Technology Solutions
// All Rights Reserved
//******************************************************************************
// File    : fileoperation.c
// Summary : Store and update device information using a linked list and a 
//           binary file.
// Note    : None
// Author  : Surya Santhosh
// Date    : 15/July/2024
//******************************************************************************

//******************************* Include Files ********************************
#include "fileOperation.h"
#include "devicelog.h"

//******************************* Local Types **********************************

//***************************** Local Constants ********************************

//***************************** Local Variables ********************************

//****************************** Local Functions *******************************
static bool fileOperationFseek(FILE **ppstFile, int8 cOffset, int8 cPosition);

//****************************.fileoperationRead.*******************************
// Purpose : To open the file.
// Inputs  : pstFile - Pointer to the binary file.
//         : cFileName -  Name of the file to be opened.
//         : cMode - Mode of opeation.
// Outputs : None
// Return  : blResult
// Notes   : None
//******************************************************************************
bool fileOperationOpen(FILE **ppstFile, int8 *cFileName, int8 *cMode)
{
    bool blResult = false;

    *ppstFile = fopen(cFileName, cMode);

    if (NULL == ppstFile)
    {
        printf("Unable to open file.");
    }
    else
    {
        blResult = true;
    }

    return blResult;
}

//****************************.fileoperationRead.*******************************
// Purpose : To open the file.
// Inputs  : pstFile - Pointer to the binary file.
//         : cFileName -  Name of the file to be opened.
//         : cMode - Mode of opeation.
// Outputs : None
// Return  : blResult
// Notes   : None
//******************************************************************************
bool fileOperationOpen(FILE **ppstFile, int8 *cFileName, int8 *cMode)
{
    bool blResult = false;

    *ppstFile = fopen(cFileName, cMode);

    if (NULL == ppstFile)
    {
        printf("Unable to open file.");
    }
    else
    {
        blResult = true;
    }

    return blResult;
}

//****************************.fileoperationClose.******************************
// Purpose : To close file.
// Inputs  : ppstFile - Pointer to the binary file 
// Outputs : None
// Return  : blResult
// Notes   : None
//******************************************************************************
bool fileOperationClose(FILE **ppstFile)
{
    bool blResult = false;

    if (NULL != *ppstFile)
    {
        if (0 != fclose(*ppstFile))
        {
            printf("Unable to closing file.");
        }
        else
        {
            *ppstFile = NULL;
            blResult = true;
        }
    }

    return blResult;
}

//****************************.fileoperationFseek.******************************
// Purpose : To move the file pointer to specific location.
// Inputs  : ppstFile - Pointer to the binary file.
//         : cOffset - It is the number of bytes to offset from the position.
//         : cPosition - The position the offset started.
// Outputs : None
// Return  : blResult
// Notes   : None
//******************************************************************************
static bool fileOperationFseek(FILE **ppstFile, int8 cOffset, int8 cPosition)
{
    bool blResult = false;

    if (NULL != ppstFile)
    {
        if (0 != fseek(*ppstFile, cOffset, cPosition))
        {
            printf("Fseek failed.");
        }
        else
        {
            blResult = true;
        }
    }

    return blResult;
}

//****************************.fileoperationFread.******************************
// Purpose : To read the data from the binary file.
// Inputs  : pstFile - Pointer to the binary file 
//         : stDeviceInfo  - Structure containing device information.
//         : cSize - The size in bytes of each element to be read.
//         : cCount - The number of elements to read.
// Outputs : None
// Return  : blResult
// Notes   : None
//******************************************************************************
bool fileOperationFread(int8 *stDeviceInfo, int8 cSize, int8 cCount, 
                        FILE *pstFile)
{
    bool blResult = false;

    if (NULL != pstFile)
    {
        if (0 != fread(stDeviceInfo, cSize, cCount, pstFile))
        {
           blResult = true;
        }
    }

    return blResult;
}

//****************************.fileoperationWrite.******************************
// Purpose : To write data from the linked list to binary file.
// Inputs  : pstFile - Pointer to the binary file 
//         : stDeviceInfo  - Structure containing device information.
//         : cSize - The size in bytes of each element to be read.
//         : cCount - The number of elements to read.
// Outputs : None
// Return  : blResult
// Notes   : None
//******************************************************************************
bool fileOperationWrite(int8 cSize, int8 cCount, FILE *pstFile, 
                        int8 *pstcurrent)
{
    bool blResult = false;

    if (NULL != pstFile && NULL != pstcurrent)
    {
        if (0 == fwrite(pstcurrent, cSize, cCount, pstFile))
        {
            printf("Fwrite failed.");
        }
        else
        {
            blResult = true;
        }
    }

    return blResult;
}

//***********************fileOperationOpenwithFseek.****************************
// Purpose : To write data from the linked list to binary file.
// Inputs  : pstFile - Pointer to the binary file.
//         : stDeviceInfo  - Structure containing device information.
//         : pstCurrent - Pointer to the node of the linked list.
// Outputs : None
// Return  : blResult
// Notes   : None
//******************************************************************************
bool fileOperationOpenwithFseek(FILE **ppstFile, int8 *cFileName, int8 *cMode)
{
    bool blResult = false;
    int8 cOffset = 0;
    int8 cPosition = SEEK_SET;

    if (true == fileOperationOpen(ppstFile, cFileName, cMode))
    {
        if (true == fileOperationFseek(ppstFile, cOffset, cPosition))
        {
            blResult = true;
        }
    }

    return blResult;
}

//EOF